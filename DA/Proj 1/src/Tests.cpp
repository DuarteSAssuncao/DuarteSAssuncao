/**
* @file Tests.cpp
* @brief Definition of tests to check graph integrity and to get some useful information
* @author G17_5
* @date 30/03/2024
*/

#include "../lib/Tests.hpp"

void print_statistics(const Graph &g) {
    double n = 0, mean = 0, variance = 0, standard_deviation = 0, median = 0, q1 = 0, q3 = 0, aqi = 0, maximum_amplitude = 0;
    size_t n_empty = 0, n_full = 0, n_invalid = 0;
    std::vector<double> sorted;
    double ratio = 0;
    for (Vertex *v: g.getVertexSet()) {
        for (Edge *e: v->getAdj()) {
            ratio = e->getFlow() / e->getWeight();
            sorted.push_back(ratio);
            mean += ratio;
            n++;
            if (e->getFlow() == 0)
                n_empty++;
            else if (e->getFlow() == e->getWeight())
                n_full++;
            else if (e->getFlow() < 0 || e->getFlow() > e->getWeight())
                n_invalid++;
        }
    }
    for (Edge *e: g.getSource()->getAdj()) {
        ratio = e->getFlow() / e->getWeight();
        sorted.push_back(ratio);
        mean += ratio;
        n++;
    }
    mean /= n;
    std::sort(sorted.begin(), sorted.end(), [](double a, double b) { return a < b; });
    for (double ratio: sorted)
        variance += std::pow(ratio - mean, 2);

    variance /= (n - 1);
    standard_deviation = std::pow(variance, 0.5);
    median = ((int) n % 2) ? sorted[(n + 1) / 2] : (sorted[n / 2] + sorted[n / 2 - 1]) / 2;
    q1 = ((int) n % 4) ? sorted[(n + 1) / 4] : (sorted[n / 4] + sorted[n / 4 - 1]) / 2;
    q3 = ((int) n % 4) ? sorted[3 * (n + 1) / 4] : (sorted[3 * n / 4] + sorted[3 * n / 4 - 1]) / 2;
    aqi = q3 - q1;
    maximum_amplitude = sorted[n - 1] - sorted[0];

    std::cout << MAGENTA << "Statistics (flow / capacity)\n";
    std::cout << YELLOW << std::setw(20) << "Number of edges: " << WHITE << n << '\n';
    std::cout << YELLOW << std::setw(20) << "Mean: " << WHITE << mean << '\n';
    std::cout << YELLOW << std::setw(20) << "Variance: " << WHITE << variance << '\n';
    std::cout << YELLOW << std::setw(20) << "Standard Deviation: " << WHITE << standard_deviation << '\n';
    std::cout << YELLOW << std::setw(20) << "Median: " << WHITE << median << '\n';
    std::cout << YELLOW << std::setw(20) << "Q1: " << WHITE << q1 << '\n';
    std::cout << YELLOW << std::setw(20) << "Q3: " << WHITE << q3 << '\n';
    std::cout << YELLOW << std::setw(20) << "AQI: " << WHITE << aqi << '\n';
    std::cout << YELLOW << std::setw(20) << "Maximum Amplitude: " << WHITE << maximum_amplitude << '\n';
    std::cout << YELLOW << std::setw(20) << "Empty Edges: " << WHITE << n_empty << '\n';
    std::cout << YELLOW << std::setw(20) << "Full Edges: " << WHITE << n_full << '\n';
    std::cout << (n_invalid == 0 ? GREEN : RED);
    std::cout /*align*/ << std::setw(20) << "Invalid Edges: " << n_invalid << '\n';
    std::cout << ANSI_RESET << "\n";
}

//! Time Complexity: O(V), Space Complexity: O(1)
void test_edges(Graph &g) {
    std::cout << "\n=============================================================================================================\n";
    std::cout << __func__ << '\n';

    unsigned int incoming = 0, outgoing = 0;
    const unsigned int real_count = 173;
    unsigned int sink_edges = g.getSink()->getIncoming().size(), source_edges = g.getSource()->getAdj().size();

    for (Vertex *v: g.getVertexSet()) {
        incoming += v->getIncoming().size();
        outgoing += v->getAdj().size();
    }

    std::cout << "Outgoing edges: " << outgoing << '\n';
    std::cout << "Incoming edges: " << incoming << '\n';
    std::cout << "Actual edges: " << real_count << '\n';
    std::cout << "Additional edges (source, sink): " << source_edges << " | " << sink_edges << '\n';
}

//! Time Complexity: O(V), Space Complexity: O(1)
void test_vertexes(Graph &g) {
    std::cout << "\n=============================================================================================================\n";
    std::cout << __func__ << '\n';

    const unsigned int cities = 22, reservoirs = 24, stations = 81, actual_vertexes = 22 + 24 + 81;
    unsigned int count_cities = 0, count_reservoirs = 0, count_stations = 0;

    for (Vertex *v: g.getVertexSet()) {
        count_cities += (v->getType() == CITY);
        count_reservoirs += (v->getType() == RESERVOIR);
        count_stations += (v->getType() == STATION);
    }

    std::cout << "Number of actual vertexes: " << actual_vertexes << ", received " << g.getVertexSet().size() << " (+2)\n";
    std::cout << "Number of actual cities: " << cities << ", received " << count_cities << '\n';
    std::cout << "Number of actual reservoirs: " << reservoirs << ", received " << count_reservoirs << '\n';
    std::cout << "Number of actual stations: " << stations << ", received " << count_stations << '\n';
}

//! Time Complexity: O(V * log V), Space Complexity: O(1)
void test_cities(Graph &g) {
    std::cout << "\n=============================================================================================================\n";
    std::cout << __func__ << '\n';

    const unsigned int cities = 22;
    std::vector<std::pair<unsigned int, Vertex *>> sorted;
    std::fstream In("csv/Cities.csv");
    std::string city, id, code, demand, population;

    getline(In, city);

    for (std::pair<unsigned int, Vertex *> p: g.getCityVertexes())
        sorted.push_back(p);

    std::sort(sorted.begin(), sorted.end(),
              [](std::pair<unsigned int, Vertex *> p1, std::pair<unsigned int, Vertex *> p2) {
                  return p1.first < p2.first;
              });

    int index = 0;

    std::cout << "(Data from file/Data from graph) : \n";
    while (getline(In, city, ',')) {
        getline(In, id, ',');
        getline(In, code, ',');
        getline(In, demand, ',');
        getline(In, population);
        std::cout << YELLOW << "City: " << WHITE << city << " / " << sorted[index].second->getCity()
                  << ", Id: " << id << " / " << sorted[index].first;
        std::cout << ", Demand: " << demand << " / " << sorted[index].second->getAdj()[0]->getWeight();
        std::cout << ", Population: " << std::stoul(population) << " / " << sorted[index].second->getPopulation()
                  << '\n';
        index++;
    }
    std::cout << '\n';
    std::cout << "Number of actual cities: " << cities << ", received " << g.getCityVertexes().size() << '\n';
}

//! Time Complexity: O(V * log V), Space Complexity: O(1)
void test_reservoirs(Graph &g) {
    std::cout << "\n=============================================================================================================\n";
    std::cout << __func__ << '\n';

    const unsigned int reservoirs = 24;

    std::vector<std::pair<unsigned int, Vertex *>> sorted;
    std::fstream In("csv/Reservoirs.csv");
    std::string reservoir, municipality, id, code, max;

    for (std::pair<unsigned int, Vertex *> p: g.getReservoirVertexes())
        sorted.push_back(p);

    std::sort(sorted.begin(), sorted.end(),
              [&](std::pair<unsigned int, Vertex *> p1, std::pair<unsigned int, Vertex *> p2) {
                  return p1.first < p2.first;
              });

    getline(In, reservoir);

    int index = 0;

    std::cout << "Data from file: \n";
    while (getline(In, reservoir, ',')) {
        getline(In, municipality, ',');
        getline(In, id, ',');
        getline(In, code, ',');
        getline(In, max);
        std::cout << YELLOW << "Reservoir: " << WHITE << reservoir << " / " << sorted[index].second->getReservoir()
                  << ", Municipality: " << municipality << " / " << sorted[index].second->getMunicipality()
                  << ", Id: " << id << " / " << sorted[index].first
                  << ", Max Delivery: " << std::stod(max) << " / "
                  << sorted[index].second->getIncoming()[0]->getWeight() << '\n';
        index++;
    }
    std::cout << "\nNumber of actual cities: " << reservoirs << ", received " << g.getReservoirVertexes().size()
              << '\n';
}

//! Time Complexity: O(V), Space Complexity: O(1)
void test_demand(Graph &g) {
    std::cout << "\n=============================================================================================================\n";
    std::cout << __func__ << '\n';
    std::cout << MAGENTA << "Water Received vs. Demand\n";
    double flow = 0, demand = 0;
    for (std::pair<unsigned int, Vertex *> p: g.getCityVertexes()) {
        flow = p.second->getAdj()[0]->getFlow();
        demand = p.second->getAdj()[0]->getWeight();
        std::cout << WHITE << std::setw(4) << p.first << ": ";
        if (flow == demand)
            std::cout << GREEN << std::setw(5) << flow << " / " << std::setw(5) << demand << '\n';
        else
            std::cout << RED << std::setw(5) << flow << WHITE << " / " << YELLOW << std::setw(5) << demand << WHITE
                      << ", missing " << BLUE << demand - flow << '\n';
    }
    std::cout << WHITE;
}

//! Time Complexity: O(V * E), Space Complexity: O(1)
void test_capacity(Graph &g) {
    std::cout << "\n=============================================================================================================\n";
    std::cout << __func__ << '\n';
    std::cout << MAGENTA << "Flow vs. Capacity\n";
    for (Vertex *v: g.getVertexSet()) {
        for (Edge *e: v->getAdj()) {
            std::cout << WHITE << std::setw(6) << e->getOrig()->getCode() << GREEN << " -> " << WHITE << std::setw(6)
                      << e->getDest()->getCode() << ": ";
            std::cout << (e->getFlow() >= 0.85 * e->getWeight() ? (e->getFlow() == e->getWeight() ? RED : YELLOW) : (
                    e->getFlow() == 0 ? CYAN : (e->getFlow() < 0 ? RED : GREEN)));
            std::cout << std::setw(5) << e->getFlow() << WHITE << " / " << e->getWeight() << '\n';
        }
    }
    std::cout << WHITE;
}

//! Time Complexity: O(V * E), Space Complexity: O(1)
void test_max_delivery(Graph &g) {
    std::cout << "\n=============================================================================================================\n";
    std::cout << __func__ << '\n';
    std::cout << MAGENTA << "Flow vs. Max Delivery\n";
    double total_flow = 0;

    std::vector<std::pair<unsigned int, Vertex *>> sorted;
    for (std::pair<unsigned int, Vertex *> p: g.getReservoirVertexes())
        sorted.push_back(p);
    std::sort(sorted.begin(), sorted.end(),
              [&](std::pair<unsigned int, Vertex *> p1, std::pair<unsigned int, Vertex *> p2) {
                  return p1.first < p2.first;
              });

    for (std::pair<unsigned int, Vertex *> p: sorted) {
        double flow = 0, max = p.second->getIncoming()[0]->getWeight();
        for (Edge *e: p.second->getAdj())
            flow += e->getFlow();
        std::cout << WHITE << std::setw(4) << p.first << ": ";
        std::cout << (flow >= 0.85 * max ? YELLOW : (flow == 0 ? CYAN : GREEN));
        std::cout << std::setw(5) << flow << WHITE << " / " << max << '\n';
        total_flow += flow;
    }

    double end_flow = 0;
    for (Edge *e: g.getSink()->getIncoming())
        end_flow += e->getFlow();
    std::cout << WHITE << "Total Flow: " << BLUE << total_flow << WHITE << "\n\n";
}

//! Time Complexity: O(V * E), Space Complexity: O(1)
void test_remove_vertexes(Graph &g) {
    std::cout << "\n=============================================================================================================\n";
    std::cout << __func__ << '\n';
    std::cout << RED << "This function removes Vertexes - don't use it in a release!\n";
    std::cout << BLUE << "Before Removal: size = " << WHITE << g.getVertexSet().size() << '\n';
    std::cout << YELLOW << "Vertex removed? " << WHITE << g.removeVertex(121) << '\n';
    std::cout << YELLOW << "Vertex removed? " << WHITE << g.removeVertex(171) << '\n';
    std::cout << YELLOW << "Vertex removed? " << WHITE << g.removeVertex(102) << '\n';
    std::cout << YELLOW << "Vertex removed? " << WHITE << g.removeVertex(202) << '\n';
    std::cout << YELLOW << "Vertex removed? " << WHITE << g.removeVertex(103) << '\n';
    std::cout << YELLOW << "Vertex removed? " << WHITE << g.removeVertex(503) << '\n';
    for (Vertex *v: g.getVertexSet()) {
        for (Edge *e: v->getAdj()) {
            std::cout << v->getCode() << " | " << e->getFlow() << " | " << e->getDest()->getCode() << '\r';
        }
    }
    for (std::pair<unsigned int, Vertex *> p: g.getCityVertexes()) {
        std::cout << p.second->getCode() << '\r';
    }
    for (std::pair<unsigned int, Vertex *> p: g.getReservoirVertexes()) {
        std::cout << p.second->getCode() << '\r';
    }
    for (std::pair<unsigned int, Vertex *> p: g.getStationVertexes()) {
        std::cout << p.second->getCode() << '\r';
    }
    std::cout << BLUE << "After removal: size = " << WHITE << g.getVertexSet().size() << '\n';
}

//! Time Complexity: O(V * E), Space Complexity: O(1)
void test_remove_edges(Graph &g) {
    std::cout << "\n=============================================================================================================\n";
    std::cout << __func__ << '\n';
    std::cout << RED << "This function removes Edges - don't use it in a release!\n";
    unsigned int count_initial = 0, count_final = 0;
    for (Vertex *v: g.getVertexSet()) {
        count_initial += v->getAdj().size();
    }
    count_initial += g.getSource()->getAdj().size();
    std::cout << BLUE << "Before Removal: size = " << WHITE << count_initial << '\n';
    std::cout << YELLOW << "Edge removed? " << WHITE << g.removeEdge(g.findVertex(12), g.findVertex(223)) << '\n';
    std::cout << YELLOW << "Edge removed? " << WHITE << g.removeEdge(g.findVertex(12), g.findVertex(233)) << '\n';
    std::cout << YELLOW << "Edge removed? " << WHITE << g.removeEdge(g.findVertex(212), g.findVertex(793)) << '\n';
    std::cout << YELLOW << "Edge removed? " << WHITE << g.removeEdge(g.findVertex(242), g.findVertex(773)) << '\n';
    std::cout << YELLOW << "Edge removed? " << WHITE << g.removeEdge(g.findVertex(13), g.findVertex(201)) << '\n';
    std::cout << YELLOW << "Edge removed? " << WHITE << g.removeEdge(g.findVertex(223), g.findVertex(21)) << '\n';
    for (Vertex *v: g.getVertexSet()) {
        count_final += v->getAdj().size();
        for (Edge *e: v->getAdj())
            std::cout << v->getCode() << " | " << e->getFlow() << " | " << e->getDest()->getCode() << '\r';
        for (Edge *e: v->getIncoming())
            std::cout << v->getCode() << " | " << e->getFlow() << " | " << e->getDest()->getCode() << '\r';
    }
    count_final += g.getSource()->getAdj().size();
    std::cout << BLUE << "After Removal: size = " << WHITE << count_final << '\n';
}

void test_flow_after_remove(Graph g) {
    std::cout << "\n=============================================================================================================\n";
    std::cout << __func__ << '\n';
    std::cout << MAGENTA
              << "The flow going through a node should be equal to the difference between the flow of the network and its flow after removing the node.\n"
              << WHITE;
    g.resetFlow();
    unsigned augmentingPaths = g.edmondsKarp();
    std::cout << "Original flow: " << g.getFlow() << " / " << g.getFlowFromSource() << "\n";
    std::cout << "Augmenting paths when using Edmonds-Karp from scratch: " << augmentingPaths << "\n";

    std::cout << "Initial statistics:\n";
    print_statistics(g);

    // to_remove: groups of nodes/edges to be removed: if bool=true, it's a vertex, otherwise it's an edge
    std::vector<std::vector<std::pair<bool, void *>>> to_remove;

    to_remove.push_back({{true, g.findVertex(42)}});
    to_remove.push_back({{true, g.findVertex(13)}});
    Edge *e1 = g.findEdge(g.findVertex(42), g.findVertex(93)), *e2 = g.findEdge(g.findVertex(93), g.findVertex(61)), *e3 = g.findEdge(g.findVertex(103), g.findVertex(93));
    to_remove.push_back({{false, e1}});
    to_remove.push_back({{false, e2}});
    to_remove.push_back({{false, e1}, {false, e3}, {false, e2}});

    for (std::vector<std::pair<bool, void *>> &vec: to_remove) {
        unsigned totalReduceFlowIterations = 0;
        double initial_flow = g.getFlow(), total_flow_affected = 0;
        for (std::pair<bool, void *> p: vec) {
            double flow_affected = 0;
            unsigned reduceFlowIterations;
            Edge *e;
            Vertex *v;
            if (p.first) { // Vertex
                v = (Vertex *) p.second;
                for (Edge *e: v->getAdj())
                    flow_affected += e->getFlow();
                std::cout << '\n' << "Node " << CYAN << v->getCode();
                g.removeVertex(v->getId(), &reduceFlowIterations);
            } else { // Edge
                e = (Edge *) p.second;
                flow_affected = e->getFlow();
                std::cout << "Edge " << CYAN << e->getOrig()->getCode() << "->" << e->getDest()->getCode();
                g.removeEdge(e->getOrig(), e->getDest(), &reduceFlowIterations);
            }
            std::cout << WHITE << " will be removed. Its flow is " << CYAN << flow_affected << WHITE << ".\n";
            std::cout << "BFSes needed to remove: " << reduceFlowIterations << "\n";
            totalReduceFlowIterations += reduceFlowIterations;
            total_flow_affected += flow_affected;
        }

        double final_flow = g.getFlow(), diff = initial_flow - final_flow;
        std::cout << "Initial network flow = " << YELLOW << initial_flow << WHITE << "\n";
        std::cout << "Final network flow = " << YELLOW << final_flow << WHITE << "\n";
        std::cout << "Expected difference = " << YELLOW << total_flow_affected << WHITE << "\n";
        std::cout << "Actual difference = " << (diff == total_flow_affected ? GREEN : RED) << diff << " / "
                  << total_flow_affected << ANSI_RESET << "\n";

        /* make sure the max flow is the same as if we did from scratch */
        augmentingPaths = g.edmondsKarp();
        double actualMaxFlow = g.getFlow();
        g.resetFlow();
        g.edmondsKarp();
        double expectedMaxFlow = g.getFlow();
        std::cout << "After Edmonds-Karp = " << (actualMaxFlow == expectedMaxFlow ? GREEN : RED)
                  << actualMaxFlow << " / " << expectedMaxFlow << ANSI_RESET << "\n";
        std::cout << "Total BFSes (reduceFlow + edmondsKarp): " << totalReduceFlowIterations << " + " << augmentingPaths
                  << "\n";

        g.restore();
        g.edmondsKarp();

        double after_restore = g.getFlow();
        std::cout << "After Restore & Edmonds-Karp = " << (after_restore == initial_flow ? GREEN : RED) << after_restore
                  << " / " << initial_flow << ANSI_RESET << "\n";
        if (after_restore != initial_flow) // this was due to a (hopefully) solved issue, I will keep this for now
            std::cout << "Flow coming out of source = " << g.getFlowFromSource() << "\n";

        print_statistics(g);
    }
}

void test_edge_statistics(Graph &g) {
    std::cout << "\n=============================================================================================================\n";
    std::cout << __func__ << '\n';
    print_statistics(g);
}

//! Time Complexity: O(V * E), Space Complexity: O(1)
void test_suite(Graph &g) {
    test_edges(g);
    test_vertexes(g);
    test_cities(g);
    test_reservoirs(g);
    test_demand(g);
    test_capacity(g);
    test_remove_vertexes(g);
    test_remove_edges(g);
    test_edge_statistics(g);
}
