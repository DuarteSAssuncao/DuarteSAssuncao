/**
 * @file Graph.cpp
 * @brief Definition of class Graph
 * @author G17_5
 * @date 17/05/2024
 */

#include "../lib/Graph.hpp"
#include <climits>

Graph::Graph() {}

Vertex *Graph::findVertex(unsigned int id) const {
    auto itr = vertexMap.find(id);
    if (itr != vertexMap.end())
        return itr->second;
    return nullptr;
}

Edge *Graph::findEdge(unsigned int source, unsigned int dest) {
    Vertex *src = this->findVertex(source), *dst = this->findVertex(dest);
    if (src == nullptr || dst == nullptr)
        return nullptr;
    for (Edge *e: src->getAdj())
        if (e->getDest() == dst)
            return e;
    return nullptr;
}

void Graph::addVertex(Vertex *v) {
    this->vertexSet.push_back(v);
    this->vertexMap.insert({v->getId(), v});
}

bool Graph::removeVertex(unsigned int id) {
    for (std::vector<Vertex *>::iterator itr = this->vertexSet.begin(); itr != this->vertexSet.end(); itr++) {
        if ((*itr)->getId() == id) {
            Vertex *to_remove = *itr;
            for (Edge *e: to_remove->getAdj()) {
#ifdef VERTEX_HAS_INCOMING
                Vertex* v = e->getDest();
                for (std::vector<Edge*>::iterator s = v->getIncoming().begin(); s < v->getIncoming().end(); s++) {
                    if ((*s)->getOrig() == to_remove) {
                        v->getIncoming().erase(s);
                        break;
                    }
                }
#endif /* VERTEX_HAS_INCOMING */
                delete e;
            }
#ifdef VERTEX_HAS_INCOMING
            for (Edge* e: to_remove->getIncoming()) {
                Vertex* v = e->getOrig();
                for (std::vector<Edge*>::iterator s = v->getAdj().begin(); s < v->getAdj().end(); s++) {
                    if ((*s)->getDest() == to_remove) {
                        v->getAdj().erase(s);
                        break;
                    }
                }
                delete e;
            }
            to_remove->getIncoming().clear();
#endif /* VERTEX_HAS_INCOMING */
            to_remove->getAdj().clear();
            delete *itr;
            this->vertexSet.erase(itr);
            this->vertexMap.erase(id);
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

bool Graph::removeEdge(unsigned int source, unsigned int dest) {
    Vertex *v1 = this->findVertex(source), *v2 = this->findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    return v1->removeEdge(v2);
}

const std::vector<Vertex *> &Graph::getVertexSet() const {
    return this->vertexSet;
}

double Graph::backtrack(unsigned int source, std::vector<Vertex *> &path) {
    std::cout << "Backtracking\n";
    Vertex *src = this->findVertex(source);
    if (!src) {
        std::cout << YELLOW << "Error: invalid vertex - " << source << ANSI_RESET;
        return -1;
    }
    double min = DBL_MAX;
    src->setVisited(true);
    backtrackDFS(src, this->vertexSet.size(), min, 0, src, {src}, path);
    std::reverse(path.begin(), path.end());
    src->setVisited(false);
    return min;
}

double Graph::bellmanHeldKarpString(unsigned int source) {
    std::cout << "Bellman Held Karp - String Version\n";
    Vertex *src = this->findVertex(source);
    if (!src) {
        std::cout << YELLOW << "Error: invalid vertex - " << source << ANSI_RESET;
        return -1;
    }
    std::vector<Vertex *> set;
    for (Vertex *vertex: this->vertexSet) {
        if (vertex != src) set.push_back(vertex);
    }

    std::vector<std::vector<double>> edges(this->vertexSet.size(), std::vector<double>(this->vertexSet.size(), 0));
    for (Vertex *a: this->vertexSet) {
        for (Vertex *b: this->vertexSet) {
            if (a != b) {
                Edge *e = this->findEdge(a->getId(), b->getId());
                edges[a->getId()][b->getId()] = e ? e->getLength() : DBL_MAX;
            } else
                edges[a->getId()][b->getId()] = 0;
        }
    }

    std::cout << "Computing Subsets\n";
    std::vector<std::string> subsets;
    computeBitSubsets(set, subsets);

    unsigned long long comb = this->vertexSet.size() - 1, previous = 1;
    std::sort(subsets.begin(), subsets.end(), [&](std::string a, std::string b) {
        return std::count_if(a.begin(), a.end(), [&](char c) { return c == '-'; }) <
               std::count_if(b.begin(), b.end(), [&](char c) { return c == '-'; });
    });

    std::cout << "Subsets Sorted\n";

    subsets.erase(subsets.begin());
    std::unordered_map<std::string, double> dp;

    for (Vertex *v: set)
        dp.insert(std::make_pair(std::to_string(v->getId()) + "-|" + std::to_string(v->getId()),
                                 edges[src->getId()][v->getId()]));

    for (unsigned int s = 2; s < this->vertexSet.size(); s++) {
        std::cout << s << '\n';
        previous = comb;
        comb = comb * (this->vertexSet.size() - s) / s;
        for (unsigned long long i = previous; i < comb + previous; i++) {
            std::string subset = subsets[i];
            std::string v1, v2;
            std::istringstream str1(subset);
            size_t index = 0;
            while (getline(str1, v1, '-')) {
                std::istringstream str2(subset);
                std::string exc = subset.substr(0, index) + subset.substr(index + v1.length() + 1);
                index += v1.length() + 1;
                double min = DBL_MAX;
                int vertex1 = std::stoi(v1);
                while (getline(str2, v2, '-')) {
                    if (v1 != v2)
                        min = std::min(min, dp.at(exc + '|' + v2) + edges[std::stoi(v2)][vertex1]);
                }
                dp[subset + '|' + v1] = min;
            }
        }
        for (unsigned long long i = 0; i < previous; i++) {
            std::string subset = subsets[i];
            std::istringstream iss(subset);
            std::string input = "";
            while (getline(iss, input, '-'))
                dp.erase(dp.find(subset + '|' + input));
        }
        unsigned long long i = 0;
        for (std::vector<std::string>::iterator itr = subsets.begin(); i < previous; i++)
            itr = subsets.erase(itr);
    }

    double optimal = DBL_MAX;
    for (Vertex *v: set)
        optimal = std::min(optimal,
                           dp.at(subsets.back() + '|' + std::to_string(v->getId())) + edges[v->getId()][source]);
    return optimal;
}

double Graph::bellmanHeldKarp(unsigned int source) {
    std::cout << "Bellman Held Karp\n";
    Vertex *src = this->findVertex(source);
    if (!src) {
        std::cout << YELLOW << "Error: invalid vertex - " << source << ANSI_RESET;
        return -1;
    }
    std::vector<Vertex *> set;
    for (Vertex *vertex: this->vertexSet) {
        if (vertex != src) set.push_back(vertex);
    }

    std::cout << "Computing Subsets\n";
    std::vector<std::vector<Vertex *>> subsets;
    computeSubsets(set, subsets);

    std::map<std::pair<std::vector<Vertex *>, Vertex *>, double> dp;

    for (Vertex *v: set) {
        Edge *e = this->findEdge(src->getId(), v->getId());
        std::vector<Vertex *> temp = {v};
        dp.insert(std::make_pair(std::make_pair(temp, v), e ? e->getLength() : DBL_MAX));
    }

    for (unsigned int s = 2; s < this->vertexSet.size(); s++) {
        std::cout << s << '\n';
        for (std::vector<Vertex *> subset: subsets) {
            if (subset.size() == s) {
                for (Vertex *v: subset) {
                    std::vector<Vertex *> temp;
                    for (Vertex *v2: subset) {
                        if (v2 != v)
                            temp.push_back(v2);
                    }
                    double min = DBL_MAX;
                    for (Vertex *v3: subset) {
                        if (v3 != v) {
                            Edge *e = this->findEdge(v3->getId(), v->getId());
                            min = std::min(min, dp.at(std::make_pair(temp, v3)) + (e ? e->getLength() : DBL_MAX));
                        }
                    }
                    dp[std::make_pair(subset, v)] = min;
                }
            }
        }
    }

    double optimal = DBL_MAX;
    for (Vertex *v: set) {
        Edge *e = this->findEdge(v->getId(), source);
        optimal = std::min(optimal, dp.at(std::make_pair(set, v)) + (e ? e->getLength() : DBL_MAX));
    }
    return optimal;
}

double Graph::nearestNeighbour(unsigned int source, std::vector<Vertex *> &path) {
    std::cout << "Nearest Neighbour\n";

    Vertex *src = this->findVertex(source);
    if (!src) {
        std::cout << YELLOW << "Error: invalid vertex - " << source << ANSI_RESET;
        return -1;
    }

    double min = DBL_MAX, sum = 0;
    unsigned int count = this->vertexSet.size() - 1;

    for (Vertex *v: this->vertexSet) {
        v->setVisited(false);
        v->setPath(nullptr);
    }

    Vertex *current = src;
    path.push_back(src);
    while (count > 0) {
        Edge *shortest = nullptr;
        unsigned int l = UINT_MAX;
        for (Edge *e: current->getAdj()) {
            if (!e->getDest()->isVisited() && e->getLength() < l) {
                l = e->getLength();
                shortest = e;
            }
        }
        if (!shortest) {
            std::cout << "The algorithm cannot complete.\n";
            path.clear();
            return -1;
        }
        current->setVisited(true);
        current = shortest->getDest();
        current->setPath(shortest);
        sum += shortest->getLength();
        path.push_back(current);
        count--;
    }

    if (count == 0) {
        Edge *end = nullptr;
        for (Edge *e: current->getAdj()) {
            if (e->getDest() == src) {
                end = e;
                break;
            }
        }
        if (!end) {
            std::cout << "The algorithm cannot complete.\n";
            path.clear();
            return -1;
        } else {
            sum += end->getLength();
            if (sum < min) {
                min = sum;
                src->setPath(end);
                path.push_back(src);
            }
        }
    }

    return min;
}

#include "../lib/MutablePriorityQueue.hpp"
void Graph::primMST(unsigned int source) {

    Vertex *src = this->findVertex(source);
    if (!src)
        return;

    struct Compare {
        bool operator()(const Vertex *a, const Vertex *b) {
            return a->getDist() < b->getDist();
        }
    };

    MutablePriorityQueue<Vertex, Compare> mpq; // needed to keep track of the closest vertices
    for (Vertex *v : vertexSet) {
        v->setVisited(false);
        v->setDist(DBL_MAX);
        v->setPath(nullptr);
    }
    src->setDist(0);
    for (Vertex *v : vertexSet)
        mpq.insert(v);

    do {
        Vertex *v = mpq.extractMin();
        v->setVisited(true);

        for (Edge *e : v->getAdj()) {
            Vertex *dest = e->getDest();
            if (!dest->isVisited() && e->getLength() < dest->getDist()) {
                dest->setPath(e);
                dest->setDist(e->getLength());
                mpq.decreaseKey(dest);
            }
        }
    } while (!mpq.empty());
}

double Graph::triangleInequality(unsigned int source, std::vector<Vertex *> &path) {
    std::cout << "Triangle Inequality\n";
    Vertex *src = this->findVertex(source);
    if (!src) {
        std::cout << YELLOW << "Error: invalid vertex - " << source << ANSI_RESET;
        return -1;
    }
    primMST(source);
    triangleInequalityDFS(src, path);
    path.push_back(src);

    double min = 0;
    size_t end = path.size() - 1;
    for (unsigned i = 0; i < end; ++i) {
        Vertex *v = path[i];
        Vertex *dst = path[i+1];

        bool found_edge = false;
        for (Edge *e : v->getAdj()) {
            if (e->getDest() == dst) {
                min  += e->getLength();
                found_edge = true;
                break;
            }
        }
        if (!found_edge)
            min += v->calcDistance(dst);
    }
    restore();
    return min;
}

int Graph::findPath(Vertex *v, std::vector<Vertex *> &path, double &cost, unsigned int &leftBehindCounter) {
    path.push_back(v);
    v->setVisited(true);

    if (path.size() == this->getVertexSet().size()) {
        for (Edge *e: v->getAdj()) {
            if (e->getDest() == path[0]) {
                // If we can go to source, we succeeded!
                path.push_back(e->getDest());
                cost += e->getLength();
                return 0;
            }
        }
        // If we cannot go to source, we failed!
        return -1;
    }

    if (path.size() + leftBehindCounter == this->getVertexSet().size()) {
        // In this case, we conclude that there is no path.
        return -1;
    }

    // Try to go to a left behind vertex:
    for (Edge *e1: v->getAdj()) {
        if (leftBehindCounter == 0) break;
        if (e1->getDest()->isLeftBehind()) {
            // For each left behind adjacent vertex:
            for (Edge *e2: e1->getDest()->getAdj()) {
                if (e2->getDest()->getPath() == nullptr) continue;
                if (e2->getDest()->getPath()->getOrig() == v) {
                    // If the left behind vertex can go back to a vertex that is a child (in the MST representation) of the vertex v
                    path.push_back(e1->getDest());
                    e1->getDest()->setLeftBehind(false);
                    leftBehindCounter--;
                    cost += e1->getLength() + e2->getLength();

                    int ret = findPath(e2->getDest(), path, cost, leftBehindCounter);
                    if (ret == -2) { // If the vertex was left behind
                        path.pop_back();
                        e1->getDest()->setLeftBehind(true);
                        leftBehindCounter++;
                        cost -= e1->getLength() + e2->getLength();
                        continue;
                    } else {
                        return ret;
                    }
                }
            }
        }
    }

    // Try to go to the next vertex in the MST:
    for (Edge *e: v->getAdj()) {
        if (e->getDest()->getPath() == nullptr) continue;
        if ((!e->getDest()->isVisited()) && (e->getDest()->getPath()->getOrig() == v)) {
            // For each child (in the MST representation) of v
            cost += e->getLength();

            int ret = findPath(e->getDest(), path, cost, leftBehindCounter);
            if (ret == -2) { // If the vertex was left behind
                cost -= e->getLength();
                continue;
            } else {
                return ret;
            }
        }
    }

    // If it isn't possible to go down the MST, try to go up to find a vertex to go next:
    if (v->getPath() == nullptr) return -1;
    Vertex *intermediate = v->getPath()->getOrig();
    while (true) {
        for (Edge *e1: intermediate->getAdj()) {
            if (e1->getDest()->getPath() == nullptr) continue;
            if ((!e1->getDest()->isVisited()) && (e1->getDest()->getPath()->getOrig() == intermediate)) {
                for (Edge *e2: v->getAdj()) {
                    if (e1->getDest() == e2->getDest()) {
                        cost += e2->getLength();

                        int ret = findPath(e2->getDest(), path, cost, leftBehindCounter);
                        if (ret == -2) { // If the vertex was left behind
                            cost -= e2->getLength();
                            continue;
                        } else {
                            return ret;
                        }
                    }
                }
            }
        }

        if (intermediate == path[0] || intermediate->getPath() == nullptr)
            break; // If the intermediate is the source, we cannot go up in the MST.
        intermediate = intermediate->getPath()->getOrig();
    }

    v->setLeftBehind(true);
    leftBehindCounter++;
    path.pop_back();
    return -2;
}

double Graph::realWorldTSP(unsigned int source, std::vector<Vertex *> &path) {
    std::cout << "Real World TSP Algorithm\n";

    Vertex *src = this->findVertex(source);
    if (!src) {
        std::cout << YELLOW << "Error: invalid vertex - " << source << ANSI_RESET;
        return -1;
    }
    primMST(source);
    for (Vertex *v: this->getVertexSet()) {
        v->setVisited(false);
        v->setLeftBehind(false);
    }

    double cost = 0;
    unsigned int leftBehindCounter = 0;
    int ret = findPath(src, path, cost, leftBehindCounter);
    if (ret < 0) return ret;
    return cost;
}

void Graph::restore() {
    for (Vertex *v: this->vertexSet) {
        v->setVisited(false);
        v->setDist(DBL_MAX);
        v->setPath(nullptr);
        v->setLeftBehind(false);
    }
}

void Graph::ensureFullyConnected(bool infinite) {
    for (Vertex *a: this->vertexSet) {
        for (Vertex *b: this->vertexSet) {
            if (a != b && this->findEdge(a->getId(), b->getId()) == nullptr) {
                if (infinite)
                    this->addEdge(a->getId(), b->getId(), DBL_MAX);
                else {
                    this->addEdge(a->getId(), b->getId(), a->calcDistance(b));
                }
            }
        }
    }
}

Graph::~Graph() {
    for (Vertex *v: this->vertexSet) {
        for (Edge *e: v->getAdj())
            delete e;
        delete v;
    }
}
