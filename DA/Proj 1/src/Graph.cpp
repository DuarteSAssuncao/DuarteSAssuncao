/**
* @file Graph.cpp
* @brief Definition of class Graph
* @author G17_5
* @date 09/03/2024
*/

#include "../lib/Graph.hpp"

Graph::Graph() {}

Graph::Graph(const Graph &other) {
    std::unordered_map<const Vertex *, Vertex *> translator;
    for (std::pair<unsigned int, Vertex *> p: other.cityVertexes) {
        Vertex *new_vertex = new Vertex(CITY, p.second->getId(), "", "", p.second->getCity(), p.second->getPopulation());
        vertexSet.push_back(new_vertex);
        cityVertexes.emplace(new_vertex->getTypeId(), new_vertex);
        translator.emplace(p.second, new_vertex);
    }

    for (std::pair<unsigned int, Vertex *> p: other.reservoirVertexes) {
        Vertex *new_vertex = new Vertex(RESERVOIR, p.second->getId(), p.second->getReservoir(), p.second->getMunicipality(), "", 0);
        vertexSet.push_back(new_vertex);
        reservoirVertexes.emplace(new_vertex->getTypeId(), new_vertex);
        translator.emplace(p.second, new_vertex);
    }

    for (std::pair<unsigned int, Vertex *> p: other.stationVertexes) {
        Vertex *new_vertex = new Vertex(STATION, p.second->getId(), "", "", "", 0);
        vertexSet.push_back(new_vertex);
        stationVertexes.emplace(new_vertex->getTypeId(), new_vertex);
        translator.emplace(p.second, new_vertex);
    }

    translator.emplace(other.sink, sink);
    translator.emplace(other.source, source);

    for (Vertex *v: other.vertexSet) {
        Vertex *new_vertex = translator[v];
        for (Edge *e: v->getAdj()) {
            Vertex *dest = translator[e->getDest()];
            Edge *new_edge = new_vertex->addEdge(dest, e->getWeight());
            new_edge->setFlow(e->getFlow());
        }
    }

    for (Edge *e: other.source->getAdj()) {
        Edge *new_edge = this->source->addEdge(translator[e->getDest()], e->getWeight());
        new_edge->setFlow(e->getFlow());
    }

    for (std::pair<unsigned int, Vertex *> p: other.cityVertexes) {
        for (auto d: p.second->getDependency()) {
            translator[p.second]->addDependency(this->findEdge(translator[d.first->getOrig()], translator[d.first->getDest()]), d.second);
        }
    }
}

Vertex *Graph::findVertex(unsigned int id) const {
    for (Vertex *v: this->vertexSet) {
        if (v->getId() == id)
            return v;
    }
    return nullptr;
}

Vertex *Graph::findVertex(const std::string &code) {
    if (code.size() < 3)
        return nullptr;
    switch (code[0]) {
        case 'P': {
            auto itr = stationVertexes.find(atoi(code.substr(3).c_str()));
            if (itr == stationVertexes.end())
                return nullptr;
            return itr->second;
        }
        case 'R': {
            auto itr = reservoirVertexes.find(atoi(code.substr(2).c_str()));
            if (itr == reservoirVertexes.end())
                return nullptr;
            return itr->second;
        }
        case 'C': {
            auto itr = cityVertexes.find(atoi(code.substr(2).c_str()));
            if (itr == cityVertexes.end())
                return nullptr;
            return itr->second;
        }
    }
    return nullptr;
}

Edge *Graph::findEdge(Vertex *src, Vertex *dst) {
    if (src == nullptr || dst == nullptr)
        return nullptr;
    for (Edge *e: src->getAdj())
        if (e->getDest() == dst)
            return e;
    return nullptr;
}

bool Graph::addVertex(Vertex *v) {
    this->vertexSet.push_back(v);
    switch (v->getType()) {
        case CITY:
            cityVertexes.insert(std::make_pair(v->getTypeId(), v));
            break;
        case RESERVOIR:
            reservoirVertexes.insert(std::make_pair(v->getTypeId(), v));
            break;
        case STATION:
            stationVertexes.insert(std::make_pair(v->getTypeId(), v));
            break;
        default:
            return false;
    }
    return true;
}

unsigned Graph::reduceFlow(Vertex *src, Vertex *dst, double limit) const {
    unsigned BFSes = 1; // there is always at least one BFS
    reduceFlowLoop:
    while (limit > 0) {
        this->setAllVisitedFalse();
        src->setVisited(true);

        std::queue<Vertex *> q;
        q.push(src);

        while (true) { // BFS
            Vertex *v = q.front();
            q.pop();

            for (Edge *e: v->getAdj()) {
                Vertex *d = e->getDest();
                if (!d->isVisited() && e->getFlow() > 0) {
                    d->setPath(e);
                    if (d != dst) {
                        d->setVisited(true);
                        q.push(d);
                    } else {
                        double min = limit;
                        for (Vertex *aux = dst; aux != src; aux = aux->getPrevious())
                            min = std::min(min, aux->getPath()->getFlow());
                        for (Vertex *aux = dst; aux != src; aux = aux->getPrevious())
                            aux->getPath()->setFlow(aux->getPath()->getFlow() - min);
                        limit -= min;
                        ++BFSes;
                        goto reduceFlowLoop;
                    }
                }
            }
            if (q.empty())
                return BFSes;
        } // BFS
    } // external loop
    return BFSes;
}

bool Graph::removeVertex(unsigned int id, unsigned *iterations) {
    for (std::vector<Vertex *>::iterator itr = this->vertexSet.begin(); itr != this->vertexSet.end(); ++itr) {
        if ((*itr)->getId() == id) {
            Vertex *to_remove = *itr;
            unsigned augmentingPaths = reduceFlow(source, to_remove, INF);
            augmentingPaths += reduceFlow(to_remove, sink, INF);
            if (iterations != nullptr)
                *iterations = augmentingPaths;
            for (Edge *e: to_remove->getAdj()) { // Erasing the edges from the incoming vector of the adjacent vertexes
                Vertex *a = e->getDest();
                for (std::vector<Edge *>::iterator s = a->getIncoming().begin(); s < a->getIncoming().end(); s++) {
                    if ((*s)->getOrig() == to_remove) {
                        a->getIncoming().erase(s);
                        break;
                    }
                }
                removedEdges.push_back(e);
            }
            for (Edge *e: to_remove->getIncoming()) { // Erasing the edges from the adjacent vector of the incoming vertexes
                Vertex *a = e->getOrig();
                for (std::vector<Edge *>::iterator s = a->getAdj().begin(); s < a->getAdj().end(); s++) {
                    if ((*s)->getDest() == to_remove) {
                        a->getAdj().erase(s);
                        break;
                    }
                }
                removedEdges.push_back(e);
            }
            to_remove->getAdj().clear();
            to_remove->getIncoming().clear();
            itr = this->vertexSet.erase(itr);
            switch (id % 10) {
                case 1:
                    this->cityVertexes.erase(to_remove->getTypeId());
                    break;
                case 2:
                    this->reservoirVertexes.erase(to_remove->getTypeId());
                    break;
                case 3:
                    this->stationVertexes.erase(to_remove->getTypeId());
                    break;
                default:
                    return false;
            }
            removedVertexes.push_back(to_remove);
            return true;
        }
    }
    return false;
}

Edge *Graph::addEdge(unsigned int source, unsigned int dest, double w) {
    Vertex *v1 = this->findVertex(source), *v2 = this->findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return nullptr;
    return v1->addEdge(v2, w);
}

bool Graph::removeEdge(Vertex *src, Vertex *dest, unsigned *iterations) {
    if (src == nullptr || dest == nullptr)
        return false;
    Edge *to_remove = src->removeEdge(dest);
    if (to_remove == nullptr)
        return false;
    double flow = to_remove->getFlow();
    unsigned augmentingPaths = reduceFlow(this->getSource(), src, flow);
    augmentingPaths += reduceFlow(dest, this->getSink(), flow);
    if (iterations != nullptr)
        *iterations = augmentingPaths;
    removedEdges.push_back(to_remove);
    return true;
}

const std::vector<Vertex *> &Graph::getVertexSet() const {
    return this->vertexSet;
}

Vertex *Graph::getSource() const {
    return this->source;
}

Vertex *Graph::getSink() const {
    return this->sink;
}

double Graph::getFlow() const {
    double flow = 0;
    for (auto p: this->getCityVertexes()) // C++17: for (auto [_, v] : this->getCityVertexes())
        flow += p.second->getAdj()[0]->getFlow();
    return flow;
}

double Graph::getFlowFromSource() const {
    double flow = 0;
    for (Edge *e: source->getAdj())
        flow += e->getFlow();
    return flow;
}

Graph::~Graph() {
    for (Vertex *v: this->vertexSet) {
        for (Edge *e: v->getAdj())
            delete e;
        delete v;
    }
    for (Vertex *v: this->removedVertexes) {
        for (Edge *e: v->getAdj())
            delete e;
        for (Edge *e: v->getIncoming())
            delete e;
        delete v;
    }
    for (Edge *e: removedEdges)
        delete e;
    for (Edge *e: this->source->getAdj())
        delete e;
    delete this->source;
    delete this->sink;
}

const std::unordered_map<unsigned int, Vertex *> &Graph::getCityVertexes() const {
    return this->cityVertexes;
}

const std::unordered_map<unsigned int, Vertex *> &Graph::getReservoirVertexes() const {
    return this->reservoirVertexes;
}

const std::unordered_map<unsigned int, Vertex *> &Graph::getStationVertexes() const {
    return this->stationVertexes;
}

void Graph::setAllVisitedFalse() const {
    for (Vertex *v: vertexSet)
        v->setVisited(false);
    source->setVisited(true);
    sink->setVisited(false);
}

unsigned Graph::edmondsKarp() {
    // to start from scratch, reset all flows before running
    unsigned iterations = 0;
    edmondsKarpLoop: // label avoids creating a bool to break out of the BFS
    ++iterations;
    this->setAllVisitedFalse();

    std::queue<Vertex *> q;
    q.push(this->source);
    while (true) {
        while (!q.empty()) { // BFS
            Vertex *v = q.front();
            q.pop();

            for (Edge *e: v->getAdj()) { // outgoing edges
                Vertex *d = e->getDest();
                if (!d->isVisited() && e->getFlow() < e->getWeight()) {
                    d->setPath(e);
                    if (d != this->sink) {
                        d->setVisited(true);
                        q.push(d);
                    } else {
                        double min = INF; // maximum flow that can go through the path found
                        for (Vertex *aux = this->sink; aux != this->source; aux = aux->getPrevious()) {
                            Edge *path = aux->getPath();
                            min = std::min(min, aux == path->getDest() ? path->getWeight() - path->getFlow()
                                                                       : path->getFlow());
                        }
                        for (Vertex *aux = this->sink; aux != this->source; aux = aux->getPrevious()) {
                            Edge *path = aux->getPath();
                            path->setFlow(path->getFlow() + (aux == path->getDest() ? min : -min));
                        }
                        goto edmondsKarpLoop;
                    }
                }
            } // outgoing edges

            for (Edge *e: v->getIncoming()) { // incoming edges
                Vertex *d = e->getOrig();
                if (!d->isVisited() && e->getFlow() > 0) {
                    d->setVisited(true);
                    d->setPath(e);
                    q.push(d);
                }
            } // incoming edges
        }
        if (q.empty())
            return iterations;
    }
}

double Graph::fordFulkerson() {
    for (Vertex *v: this->getVertexSet()) {
        for (Edge *e: v->getAdj())
            e->setFlow(0); // Setting the flow of all the edges as 0.
    }

    double totalFlow = 0;
    bool found = false;
    double flow = 0;
    std::vector<Edge *> toIncreaseFlow;
    std::vector<Edge *> toDecreaseFlow;

    do {
        totalFlow += flow;
        for (Edge *e: toIncreaseFlow) e->setFlow(e->getFlow() + flow); // Update flow (increase)
        for (Edge *e: toDecreaseFlow) e->setFlow(e->getFlow() - flow); // Update flow (decrease)

        toIncreaseFlow = {};
        toDecreaseFlow = {};
        flow = INF;
        found = false;  // Resetting values

        for (Vertex *v: this->getVertexSet()) v->setVisited(false); // Set all vertexes as non visited.

        recursiveAugmentingPath(this->source, toIncreaseFlow, toDecreaseFlow, flow, found); // Try to find path
    } while (found);

    return totalFlow;
}

void Graph::recursiveAugmentingPath(Vertex *v, std::vector<Edge *> &toIncreaseFlow, std::vector<Edge *> &toDecreaseFlow,
                                    double &flow, bool &found) {
    v->setVisited(true);
    for (Edge *e: v->getAdj()) {
        Vertex *w = e->getDest();
        if (!w->isVisited() && e->getFlow() < e->getWeight()) {
            if (w == this->sink) { // If the vertex is the target
                found = true;
                flow = e->getWeight() - e->getFlow();
                toIncreaseFlow.push_back(e);
                return;
            }
            recursiveAugmentingPath(w, toIncreaseFlow, toDecreaseFlow, flow, found);
            if (found) { // If the target was found ...
                flow = std::min(flow, e->getWeight() - e->getFlow()); // ... the flow for that path must be updated
                toIncreaseFlow.push_back(e);
                return;
            }
        }
    }

    for (Edge *e: v->getIncoming()) { // The same loop as before, but now, we consider back-edges.
        Vertex *w = e->getOrig();
        if (!w->isVisited() && e->getFlow() > 0) {
            // Assuming that the vertex is not the target.
            recursiveAugmentingPath(w, toIncreaseFlow, toDecreaseFlow, flow, found);
            if (found) { // If the target was found ...
                flow = std::min(flow, e->getFlow()); // ... the flow for that path must be updated
                toDecreaseFlow.push_back(e);
                return;
            }
        }
    }
}

void Graph::reset() {
    for (Vertex *v: this->vertexSet) {
        v->setVisited(false);
        v->setPath(nullptr);
        for (Edge *e: v->getAdj())
            e->setFlow(0);
    }
    for (Edge *e: this->source->getAdj())
        e->setFlow(0);
}

void Graph::resetFlow() {
    for (Vertex *v: vertexSet)
        for (Edge *e: v->getAdj())
            e->setFlow(0);
    for (Edge *e: source->getAdj())
        e->setFlow(0);
}

void Graph::restore() {
    for (Vertex *v: removedVertexes)
        this->addVertex(v);
    for (Edge *e: removedEdges) {
        e->setFlow(0);
        e->getOrig()->getAdj().push_back(e);
        e->getDest()->getIncoming().push_back(e);
    }
    removedVertexes.clear();
    removedEdges.clear();
}

const std::vector<Vertex *> &Graph::getRemovedVertexes() const {
    return removedVertexes;
}

const std::vector<Edge *> &Graph::getRemovedEdges() const {
    return removedEdges;
}

void Graph::calculateDependency() {
    for (Vertex *a: this->vertexSet) {
        if (a->getType() == CITY) continue;
        for (Edge *to_remove: a->getAdj()) {
            Graph copy = Graph(*this);
            this->removeEdge(to_remove->getOrig(), to_remove->getDest());
            this->edmondsKarp();
            for (auto c: this->cityVertexes) {
                double difference = copy.getCityVertexes().at(c.second->getTypeId())->getAdj()[0]->getFlow() -
                                    c.second->getAdj()[0]->getFlow();
                if (difference > 0) {
                    c.second->addDependency(to_remove, difference);
                }
            }
            this->restore();
            this->edmondsKarp();
        }
    }
}
