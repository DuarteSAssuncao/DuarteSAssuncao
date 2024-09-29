/**
 * @file Parser.cpp
 * @brief Definition of Parser function and its auxiliary functions
 * @author G17_5
 * @date 17/04/2024
 */

#include "../lib/Parser.hpp"
#include <climits>

//! Time Complexity: O(1), Space Complexity: O(1)
bool check_file(const std::string &filename, std::ifstream &In) {
    if (filename.substr(filename.length() - 4, 4) == ".csv" && In.good())
        return true;
    std::cerr << "The filename " << filename << " is invalid\n";
    return false;
}

//! Ignores the first line if its first character isn't a digit
static void check_first_line(std::ifstream &in) {
    int c = in.peek();
    if (c < '0' || c > '9') {
        std::cout << "Ignoring first line..." << std::endl;
        std::string dummy;
        getline(in, dummy);
    }
}

//! Time Complexity: O(t), Space Complexity: O(t), t - total number of lines
void parse(Graph &network, const std::string &edges_csv, const std::string &vertexes_csv) {
    std::ifstream Edge(edges_csv);
    std::ifstream Vertex(vertexes_csv);
    if (check_file(edges_csv, Edge)) {
        if (vertexes_csv.empty()) {
            parseVertexesAndEdges(network, edges_csv);
            std::cout << ANSI_RESET << std::setw(25) << "Parse Vertexes and Edges " << std::setw(18) << edges_csv;
            std::cout << GREEN << " OK" << ANSI_RESET << '\n';
        } else if (check_file(vertexes_csv, Vertex)) {
            unsigned int index = edges_csv.find_last_of('_');
            unsigned int limit;
            try {
                // try to get number of nodes
                limit = std::stoi(edges_csv.substr(index + 1, edges_csv.length() - 4 - index));
                std::cout << "Found a number after the last '_'! Will only read " << limit << " nodes" << std::endl;
            } catch (std::invalid_argument &e) {
                // if it failed to get number of nodes, just read them all
                limit = UINT_MAX;
            }
            parseVertexes(network, vertexes_csv, limit);
            std::cout << ANSI_RESET << std::setw(17) << "Parse Vertexes " << std::setw(45) << vertexes_csv << GREEN << " OK"
                      << '\n';
            std::cout << "Number of nodes: " << network.getVertexSet().size() << std::endl;
            parseEdges(network, edges_csv);
            std::cout << ANSI_RESET << std::setw(17) << "Parse Edges " << std::setw(45) << edges_csv;
            std::cout << GREEN << " OK" << ANSI_RESET << '\n';

            size_t n_edges = 0;
            for (auto v: network.getVertexSet())
                n_edges += v->getAdj().size();
            std::cout << "Number of edges: " << n_edges << std::endl;
        } else
            std::cout << "The file " << vertexes_csv << " is invalid\n";
    } else
        std::cout << "The file " << edges_csv << " is invalid\n";
}

//! Time Complexity: O(V), Space Complexity: O(V)
void parseVertexes(Graph &network, const std::string &file, unsigned int limit) {
    std::ifstream fs(file);
    if (check_file(file, fs)) {
        check_first_line(fs);
        std::string id, latitude, longitude;
        while (getline(fs, id, ',') && limit > 0) {
            getline(fs, latitude, ',');
            getline(fs, longitude);
            network.addVertex(new Vertex(std::stoul(id), std::stod(latitude), std::stod(longitude)));
            limit--;
        }
    }
}

//! Time Complexity: O(E), Space Complexity: O(E)
void parseEdges(Graph &network, const std::string &file) {
    std::ifstream fs(file);
    if (!check_file(file, fs)) return;
    check_first_line(fs);

    std::string src, dest, dist;
    while (getline(fs, src, ',')) {
        getline(fs, dest, ',');
        getline(fs, dist);
        Vertex *a = network.findVertex(std::stoul(src));
        Vertex *b = network.findVertex(std::stoul(dest));
        a->addEdge(b, std::stod(dist));
        b->addEdge(a, std::stod(dist));
    }
}

//! Time Complexity: O(E), Space Complexity: O(E + V)
void parseVertexesAndEdges(Graph &network, const std::string &file) {
    std::ifstream fs(file);
    if (!check_file(file, fs)) return;
    check_first_line(fs);

    std::unordered_map<unsigned long, Vertex *> vertexes;
    std::string src, dest, dist, line;
    while (getline(fs, line)) {
        std::istringstream iss(line);
        getline(iss, src, ',');
        getline(iss, dest, ',');
        getline(iss, dist);
        if (src.empty()) break;
        unsigned long srcID = std::stoul(src), destID = std::stoul(dest);
        if (vertexes.find(srcID) == vertexes.end())
            vertexes.insert(std::make_pair(srcID, new Vertex(srcID, 0, 0)));
        if (vertexes.find(destID) == vertexes.end())
            vertexes.insert(std::make_pair(destID, new Vertex(destID, 0, 0)));
        vertexes.at(srcID)->addEdge(vertexes.at(destID), std::stod(dist));
        vertexes.at(destID)->addEdge(vertexes.at(srcID), std::stod(dist));
    }
    for (auto p: vertexes)
        network.addVertex(p.second);
}
