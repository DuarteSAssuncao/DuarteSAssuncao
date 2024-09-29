/**
* @file Parser.cpp
* @brief Definition of Parser function and its auxiliary functions
* @author G17_5
* @date 17/03/2024
*/

#include "../lib/Parser.hpp"

//! Time Complexity: O(1), Space Complexity: O(1)
bool check_file(const std::string filename, std::fstream &In) {
    if (filename.substr(filename.length() - 4, 4) == ".csv" && In.good())
        return true;
    std::cerr << "The filename " << filename << " is invalid\n";
    return false;
}

//! Time Complexity: O(t), Space Complexity: O(t), t - total number of lines
Graph parse(
        const std::string cities_csv,
        const std::string pipes_csv,
        const std::string reservoirs_csv,
        const std::string stations_csv) {
    Graph network;

    parseCities(network, cities_csv);
    std::cout << WHITE << std::setw(17) << "Parse Cities " << std::setw(18) << cities_csv << GREEN << " OK" << '\n';

    parseReservoirs(network, reservoirs_csv);
    std::cout << WHITE << std::setw(17) << "Parse Reservoirs " << std::setw(18) << reservoirs_csv << GREEN << " OK"
              << '\n';

    parseStations(network, stations_csv);
    std::cout << WHITE << std::setw(17) << "Parse Stations " << std::setw(18) << stations_csv << GREEN << " OK" << '\n';

    parsePipes(network, pipes_csv);
    std::cout << WHITE << std::setw(17) << "Parse Pipes " << std::setw(18) << pipes_csv << GREEN << " OK" << WHITE
              << '\n';

    return network;
}

//! Time Complexity: O(n), Space Complexity: O(n), n - number of lines
void parseCities(Graph &network, const std::string file) {
    std::fstream fs(file);
    if (check_file(file, fs)) {
        std::string city, id, demand, population;
        getline(fs, city);
        while (getline(fs, city, ',')) {
            getline(fs, id, ',');
            getline(fs, demand, ',');
            getline(fs, demand, ',');
            getline(fs, population);
            unsigned int d = std::stoul(demand);
            Vertex *v = new Vertex(
                    CITY,
                    (unsigned int) (std::stoul(id) * 10 + 1),
                    "",
                    "",
                    city,
                    (unsigned int) std::stoul(population));
            v->addEdge(network.getSink(), d);
            network.addVertex(v);
        }
    }
}

//! Time Complexity: O(1), Space Complexity: O(1)
Vertex *computeVertex(Graph &network, std::string s) {  // Depending on the code, the selected Vertex is different
    Vertex *v = nullptr;
    switch (s[0]) {
        case 'C':
            v = network.getCityVertexes().at((unsigned int) std::stoul(s.substr(2, s.length() - 2)));
            break;
        case 'R':
            v = network.getReservoirVertexes().at((unsigned int) std::stoul(s.substr(2, s.length() - 2)));
            break;
        case 'P':
            v = network.getStationVertexes().at((unsigned int) (std::stoul(s.substr(3, s.length() - 3))));
            break;
        default:
            std::cerr << "The code " << s << " is invalid" << std::endl;
    }
    return v;
}

//! Time Complexity: O(n), Space Complexity: O(n), n - number of lines
void parsePipes(Graph &network, const std::string file) {
    std::fstream fs(file);
    if (check_file(file, fs)) {                           // The file exists and is a comma-separated one
        std::string source, dest, capacity, direction;    // The code isn't necessary
        getline(fs, source);                              // The header line will be ignored
        while (getline(fs, source, ',')) {                // While the file isn't over
            getline(fs, dest, ',');
            getline(fs, capacity, ',');                   // Code skipped
            getline(fs, direction);
            Vertex *src = computeVertex(network, source), *destination = computeVertex(network, dest);
            double weight = std::stod(capacity);
            src->addEdge(destination, weight);
            if (direction[0] == '0')                      // Bidirectional
                destination->addEdge(src, weight);
        }
    }
}

//! Time Complexity: O(n), Space Complexity: O(n), n - number of lines
void parseReservoirs(Graph &network, const std::string file) {
    std::fstream fs(file);
    if (check_file(file, fs)) {          // The file exists and is a comma-separated one
        std::string r, m, id, max;       // The code isn't necessary
        getline(fs, r);                  // The header line will be ignored
        while (getline(fs, r, ',')) {    // While the file isn't over
            getline(fs, m, ',');
            getline(fs, id, ',');
            getline(fs, max, ',');       // Code skipped
            getline(fs, max);
            Vertex *v = new Vertex(RESERVOIR, (unsigned int) std::stoul(id) * 10 + 2, r, m);
            // The last number of the ID yields the type
            network.addVertex(v);
            network.getSource()->addEdge(v, std::stod(max));
        }
    }
}

//! Time Complexity: O(n), Space Complexity: O(n), n - number of lines
void parseStations(Graph &network, const std::string file) {
    std::fstream fs(file);
    if (check_file(file, fs)) {            // The file exists and is a comma-separated one
        std::string id, code;              // The code isn't necessary
        getline(fs, id);                   // The header line will be ignored
        while (getline(fs, id, ',')) {     // While the file isn't over
            getline(fs, code);
            network.addVertex(new Vertex(STATION, (unsigned int) std::stoul(id) * 10 + 3)); // The last number of the ID yields the type
        }
    }
}
