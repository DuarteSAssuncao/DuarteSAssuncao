/**
 * @file Runtime.cpp
 * @brief Definition of functions used to run the program
 * @author G17_5
 * @date 06/04/2024
 */

#include "../lib/Runtime.hpp"
#include <algorithm>
#include <iomanip>
#include <cmath>

Runtime::Runtime(Graph *graph): network(*graph) {}

static void print_pipes_statistics(const Graph &g);

void Runtime::run(){
    std::cout << WHITE << "\nWelcome to our project!\nType " << GREEN << "help" << WHITE << " to learn the available commands." << std::endl;
    while(true){
        if (std::cin.eof()) break; // CTRL-D
        std::cout << "> ";
        std::vector<std::string> command = readCommand();
        if (command.empty()) continue;
        std::cout << std::endl;
        if (command[0] == "exit") break;
        else if(command[0] == "help") help(command);
        else if(command[0] == "display_city") displayCity(command);
        else if(command[0] == "display_reservoir") displayReservoir(command);
        else if(command[0] == "display_station") displayStation(command);
        else if(command[0] == "needy_cities") needyCities(command);
        else if(command[0] == "remove") remove(command);
        else if(command[0] == "remove_pipe") removePipe(command);
        else if(command[0] == "restore") restore(command);
        else if(command[0] == "show_dependency") showDependency(command);
        else if(command[0] == "pipes_statistics") print_pipes_statistics(network);
        else{
            std::cout << RED << "Error:" << WHITE << "No such command. Type " << GREEN << "help" << WHITE << " to learn the available commands.\n";
        }
    }
    std::cout << RED << "Terminating program...\n"
              << WHITE << "Hope to see you soon!\n";
}

/**
 * @brief Prints statistics about the pipes
 * @param const Graph& g: graph
 * @return void
 * @note This function is static
 * @note Time Complexity: O(E * log E + V), Space Complexity: O(1)
 */
void Runtime::print_pipes_statistics(const Graph &g) {
    size_t n = 0;
    double mean = 0, variance = 0, standard_deviation = 0, median = 0, q1 = 0, q3 = 0, aqi = 0, maximum_amplitude = 0;
    size_t n_empty = 0, n_full = 0;
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
        }
    }
    for (auto p : g.getCityVertexes()) {
        Edge *e = p.second->getAdj()[0]; // this is not an actual pipe, it's an auxiliary edge
        if (e->getFlow() == 0) n_empty--;
        else if (e->getFlow() == e->getWeight()) n_full--;
        mean -= e->getFlow() / e->getWeight();
    }
    n -= g.getCityVertexes().size();
    mean /= n;
    std::sort(sorted.begin(), sorted.end(), [](double a, double b) { return a < b; });
    for (double ratio: sorted)
        variance += std::pow(ratio - mean, 2);

    variance /= (double) (n - 1);
    standard_deviation = std::pow(variance, 0.5);
    median = (n % 2) ? sorted[(n + 1) / 2] : (sorted[n / 2] + sorted[n / 2 - 1]) / 2;
    q1 = (n % 4) ? sorted[(n + 1) / 4] : (sorted[n / 4] + sorted[n / 4 - 1]) / 2;
    q3 = (n % 4) ? sorted[3 * (n + 1) / 4] : (sorted[3 * n / 4] + sorted[3 * n / 4 - 1]) / 2;
    aqi = q3 - q1;
    maximum_amplitude = sorted[n - 1] - sorted[0];

    std::cout << MAGENTA << "Statistics (flow / capacity)\n";
    std::cout << YELLOW << std::setw(20) << "Number of pipes: " << WHITE << n << '\n';
    std::cout << YELLOW << std::setw(20) << "Mean: " << WHITE << mean << '\n';
    std::cout << YELLOW << std::setw(20) << "Variance: " << WHITE << variance << '\n';
    std::cout << YELLOW << std::setw(20) << "Standard Deviation: " << WHITE << standard_deviation << '\n';
    std::cout << YELLOW << std::setw(20) << "Median: " << WHITE << median << '\n';
    std::cout << YELLOW << std::setw(20) << "Q1: " << WHITE << q1 << '\n';
    std::cout << YELLOW << std::setw(20) << "Q3: " << WHITE << q3 << '\n';
    std::cout << YELLOW << std::setw(20) << "AQI: " << WHITE << aqi << '\n';
    std::cout << YELLOW << std::setw(20) << "Maximum Amplitude: " << WHITE << maximum_amplitude << '\n';
    std::cout << YELLOW << std::setw(20) << "Empty Pipes: " << WHITE << n_empty << '\n';
    std::cout << YELLOW << std::setw(20) << "Full Pipes: " << WHITE << n_full << '\n';
    std::cout << ANSI_RESET << "\n";
}

std::vector<std::string> Runtime::readCommand(){
    std::vector<std::string> ret;

    std::string command;
    getline(std::cin, command);
    // std::cin >> command;

    std::istringstream iss = std::istringstream(command);
    std::string arg;
    while(getline(iss, arg, ' ')){
        ret.push_back(arg);
        arg.clear();
    }

    return ret;
}

void Runtime::help(std::vector<std::string> args){
    if (args.size() != 1) {
        std::cout << RED << "Error: expected no arguments." << ANSI_RESET << std::endl;
        return;
    }

    std::cout << "List of available commands:"
              << std::endl << std::endl
              << "    " << GREEN << "exit:" << CYAN << "              takes no arguments" << WHITE << std::endl
              << "        Terminates the program."
              << std::endl << std::endl
              << "    " << GREEN << "help:" << CYAN << "              takes no arguments" << WHITE << std::endl
              << "        Prints this list of commands."
              << std::endl << std::endl
              << "    " << GREEN << "display_city:" << CYAN << "      takes 1 argument" << YELLOW << "    display_city <city_id | -all>" << WHITE << std::endl
              << "        Displays the City with that id, or all of them in case the flag -all is used."
              << std::endl << std::endl
              << "    " << GREEN << "display_reservoir:" << CYAN << " takes 1 argument" << YELLOW << "    display_reservoir <reservoir_id | -all>" << WHITE << std::endl
              << "        Displays the Reservoir with that id, or all of them in case the flag -all is used."
              << std::endl << std::endl
              << "    " << GREEN << "display_station:" << CYAN << "   takes 1 argument" << YELLOW << "    display_station <station_id | -all>" << WHITE << std::endl
              << "        Displays the Pumping Station with that id, or all of them in case the flag -all is used."
              << std::endl << std::endl
              << "    " << GREEN << "needy_cities:" << CYAN << "      takes no arguments" << WHITE << std::endl
              << "        Displays the cities whose water demand is not fulfilled by the network."
              << std::endl << std::endl
              << "    " << GREEN << "remove:" << CYAN << "            takes 1 argument" << YELLOW << "    remove <code>" << WHITE << std::endl
              << "        Removes a City, Reservoir, or a Pumping Station from the network and prints the Cities/Reservoirs affected." << std::endl
              << "        Do not forget to use the " << GREEN << "restore" << WHITE << " command to add the removed location again to the network."
              << std::endl << std::endl
              << "    " << GREEN << "remove_pipe:" << CYAN << "       takes 2 arguments" << YELLOW << "   remove_pipe <code_origin> <code_destination>" << WHITE << std::endl
              << "        Removes a Pipe from the network and prints the Cities/Reservoirs affected." << std::endl
              << "        Do not forget to use the " << GREEN << "restore" << WHITE << " command to add the removed location again to the network."
              << std::endl << std::endl
              << "    " << GREEN << "restore:" << CYAN << "           takes no arguments" << WHITE << std::endl
              << "        Undoes the previous removal. The network will be as in the beginning."
              << std::endl << std::endl
              << "    " << GREEN << "show_dependency:" << CYAN << "   takes 1 argument" << YELLOW << "    show_dependency <city_id>" << WHITE << std::endl
              << "        For a given City, shows which Pipelines, if ruptured, would affect the amount of water reaching the City."
              << std::endl << std::endl
              << "    " << GREEN << "pipes_statistics:" << CYAN << "  takes no arguments" << WHITE << std::endl
              << "        Displays statistics about the flow/capacity ratio of the pipes, like their average ratio, amount of empty/full pipes, etc."
              << std::endl << std::endl;
}

void Runtime::displayCity(std::vector<std::string> args){
    if (args.size() != 2) {
        std::cout << RED << "Error: expected 1 argument." << ANSI_RESET << std::endl;
        return;
    }

    if(args[1] == "-all") {
        std::cout << YELLOW << "Cities:\n" << WHITE;
        std::vector<Vertex *> cities;
        for (auto city: network.getCityVertexes()) cities.push_back(city.second);
        std::sort(cities.begin(), cities.end(), [] (Vertex * c1, Vertex * c2) {return c1->getTypeId() < c2->getTypeId();});
        for (Vertex *city: cities) {
            std::cout << "  " << std::setw(2) << city->getTypeId() << ": " << city->getCity() << std::endl;
            std::cout << "     Demand: " << city->getAdj()[0]->getWeight() << std::endl;
            std::cout << "     Water reaching: " << city->getAdj()[0]->getFlow() << std::endl;
            std::cout << "     Population: " << city->getPopulation() << std::endl << std::endl;
        }
    } else {
        try{
            unsigned int id = std::stoul(args[1]);
            Vertex *city = network.getCityVertexes().at(id);
            std::cout << "  " << std::setw(2) << city->getTypeId() << ": " << city->getCity() << std::endl;
            std::cout << "     Demand: " << city->getAdj()[0]->getWeight() << std::endl;
            std::cout << "     Water reaching: " << city->getAdj()[0]->getFlow() << std::endl;
            std::cout << "     Population: " << city->getPopulation() << std::endl << std::endl;
        }catch(...){
            std::cout << RED << "Error: " << args[1] << " is not a valid id." << WHITE << std::endl;
        }
    }
}

void Runtime::displayReservoir(std::vector<std::string> args) {
    if (args.size() != 2) {
        std::cout << RED << "Error: expected 1 argument." << ANSI_RESET << std::endl;
        return;
    }

    if(args[1] == "-all") {
        std::cout << YELLOW << "Reservoirs:\n" << WHITE;
        std::vector<Vertex *> reservoirs;
        for (auto reservoir: network.getReservoirVertexes()) reservoirs.push_back(reservoir.second);
        std::sort(reservoirs.begin(), reservoirs.end(), [] (Vertex * r1, Vertex * r2) {return r1->getTypeId() < r2->getTypeId();});
        for (Vertex *reservoir: reservoirs) {
            std::cout << "  " << std::setw(2) << reservoir->getTypeId() << ": " << reservoir->getReservoir() << std::endl;
            std::cout << "     Max delivery: " << reservoir->getIncoming()[0]->getWeight() << std::endl;
            std::cout << "     Water supplying: " << reservoir->getIncoming()[0]->getFlow() << std::endl;
            std::cout << "     Municipality: " << reservoir->getMunicipality() << std::endl << std::endl;
        }
    } else {
        try{
            unsigned int id = std::stoul(args[1]);
            Vertex *reservoir = network.getReservoirVertexes().at(id);
            std::cout << "  " << std::setw(2) << reservoir->getTypeId() << ": " << reservoir->getReservoir() << std::endl;
            std::cout << "     Max delivery: " << reservoir->getIncoming()[0]->getWeight() << std::endl;
            std::cout << "     Water supplying: " << reservoir->getIncoming()[0]->getFlow() << std::endl;
            std::cout << "     Municipality: " << reservoir->getMunicipality() << std::endl << std::endl;
        }catch(...){
            std::cout << RED << "Error: " << args[1] << " is not a valid id." << WHITE << std::endl;
        }
    }
}

void Runtime::displayStation(std::vector<std::string> args) {
    if (args.size() != 2) {
        std::cout << RED << "Error: expected 1 argument." << ANSI_RESET << std::endl;
        return;
    }

    if(args[1] == "-all") {
        std::cout << YELLOW << "Stations:\n" << WHITE;
        std::vector<Vertex *> stations;
        for (auto station: network.getStationVertexes()) stations.push_back(station.second);
        std::sort(stations.begin(), stations.end(), [] (Vertex * s1, Vertex * s2) {return s1->getTypeId() < s2->getTypeId();});
        for (Vertex *station: stations) {
            std::cout << "  " << "Station " << std::setw(2) << station->getTypeId() << std::endl;
            double passing = 0;
            for (Edge *e: station->getIncoming()) passing += e->getFlow();
            std::cout << "     Water passing: " << passing << std::endl;
        }
    } else {
        try{
            unsigned int id = std::stoul(args[1]);
            Vertex *station = network.getStationVertexes().at(id);
            std::cout << "  " << "Station " << std::setw(2) << station->getTypeId() << std::endl;
            double passing = 0;
            for (Edge *e: station->getIncoming()) passing += e->getFlow();
            std::cout << "     Water passing: " << passing << std::endl;
        }catch(...){
            std::cout << RED << "Error: " << args[1] << " is not a valid id." << WHITE << std::endl;
        }
    }
}

void Runtime::needyCities(std::vector<std::string> args) {
    if (args.size() != 1) {
        std::cout << RED << "Error: expected no arguments." << ANSI_RESET << std::endl;
        return;
    }

    double totalDemand = 0, totalReaching = 0, totalMissing = 0;
    for (auto city: network.getCityVertexes()) {
        if (city.second->getDemand() > city.second->getAdj()[0]->getFlow()) { // If the city's demand is higher than the water reaching it
            std::cout << "  " << std::setw(2) << city.second->getTypeId() << ": " << city.second->getCity() << std::endl;
            std::cout << "     Demand: " << YELLOW << city.second->getDemand() << WHITE << std::endl;
            std::cout << "     Water reaching: " << CYAN << city.second->getAdj()[0]->getFlow() << WHITE << std::endl;
            std::cout << "     Missing: " << RED << city.second->getDemand() - city.second->getAdj()[0]->getFlow() << WHITE << std::endl;
            totalDemand += city.second->getDemand();
            totalReaching += city.second->getAdj()[0]->getFlow();
            totalMissing += city.second->getDemand() - city.second->getAdj()[0]->getFlow();
        }
    }
    std::cout << std::endl;
    std::cout << GREEN << "  In Total:" << WHITE << std::endl;
    std::cout << "     Demand: " << YELLOW << totalDemand << WHITE << std::endl;
    std::cout << "     Water reaching: " << CYAN << totalReaching << WHITE << std::endl;
    std::cout << "     Missing: " << RED << totalMissing << WHITE << std::endl;
}

void Runtime::printAffected(Graph &graph, const std::vector<Vertex *>& affectedCities, const std::vector<Vertex *>& affectedReservoirs) {
    if (!affectedCities.empty()) {
        std::cout << YELLOW << "Affected Cities:" << WHITE << std::endl;
        for (Vertex *city: affectedCities) {
            std::cout << "  " << std::setw(2) << city->getTypeId() << ": " << city->getCity() << std::endl
                      << "     Flow before removal: "
                      << graph.getCityVertexes().at(city->getTypeId())->getAdj()[0]->getFlow()
                      << std::endl
                      << "     Flow after removal: "
                      << network.getCityVertexes().at(city->getTypeId())->getAdj()[0]->getFlow()
                      << std::endl
                      << "     Difference: "
                      << graph.getCityVertexes().at(city->getTypeId())->getAdj()[0]->getFlow() -
                         network.getCityVertexes().at(city->getTypeId())->getAdj()[0]->getFlow()
                      << std::endl;
        }
        std::cout << std::endl;
    }
    if (!affectedReservoirs.empty()) {
        std::cout << YELLOW << "Affected Reservoirs:" << WHITE << std::endl;
        for (Vertex *reservoir: affectedReservoirs) {
            std::cout << "  " << std::setw(2) << reservoir->getTypeId() << ": " << reservoir->getReservoir() << std::endl
                      << "     Flow before removal: "
                      << graph.getReservoirVertexes().at(reservoir->getTypeId())->getIncoming()[0]->getFlow()
                      << std::endl
                      << "     Flow after removal: "
                      << network.getReservoirVertexes().at(reservoir->getTypeId())->getIncoming()[0]->getFlow()
                      << std::endl
                      << "     Difference: "
                      << graph.getReservoirVertexes().at(reservoir->getTypeId())->getIncoming()[0]->getFlow() -
                         network.getReservoirVertexes().at(reservoir->getTypeId())->getIncoming()[0]->getFlow()
                      << std::endl;
        }
        std::cout << std::endl;
    }

}

void Runtime::remove(std::vector<std::string> args) {
    /*if (!network.getRemovedVertexes().empty() or !network.getRemovedEdges().empty()) {
        std::cout << RED << "Warning:" << WHITE << "Please, restore the graph before removing anything else." << std::endl;
        return;
    }*/

    if (args.size() != 2) {
        std::cout << RED << "Error: expected 1 argument." << ANSI_RESET << std::endl;
        return;
    }

    Vertex *v = network.findVertex(args[1]);
    if (v == nullptr) {
        std::cout << RED << "Error: \"" << args[1] << "\" not found." << ANSI_RESET << std::endl;
        return;
    }

    Graph graph = network;
    network.removeVertex(v->getId());
    network.edmondsKarp();
    std::vector<Vertex *> affectedCities;
    std::vector<Vertex *> affectedReservoirs;
    for (auto c: network.getCityVertexes()) {
        if (c.second->getAdj()[0]->getFlow() != graph.getCityVertexes().at(c.second->getTypeId())->getAdj()[0]->getFlow()) {
            affectedCities.push_back(c.second);
        }
    }
    for (auto r: network.getReservoirVertexes()) {
        if (r.second->getIncoming()[0]->getFlow() != graph.getReservoirVertexes().at(r.second->getTypeId())->getIncoming()[0]->getFlow()) {
            affectedReservoirs.push_back(r.second);
        }
    }

    if (v->getType() == CITY) printAffected(graph, {}, affectedReservoirs);
    if (v->getType() == RESERVOIR) printAffected(graph, affectedCities, {});
    if (v->getType() == STATION) printAffected(graph, affectedCities, affectedReservoirs);
}

void Runtime::removePipe(std::vector<std::string> args) {
    /*if (!network.getRemovedVertexes().empty() or !network.getRemovedEdges().empty()) {
        std::cout << RED << "Warning:" << WHITE << "Please, restore the graph before removing anything else." << std::endl;
        return;
    }*/

    if (args.size() != 3) {
        std::cout << RED << "Error: expected 2 arguments." << ANSI_RESET << std::endl;
        return;
    }

    Vertex *v = network.findVertex(args[1]);
    if (v == nullptr) {
        std::cout << RED << "Error: \"" << args[1] << "\" not found." << ANSI_RESET << std::endl;
        return;
    }
    Vertex *d = network.findVertex(args[2]);
    if (d == nullptr) {
        std::cout << RED << "Error: \"" << args[2] << "\" not found." << ANSI_RESET << std::endl;
        return;
    }

    Edge *e = nullptr;
    for (Edge *edge: v->getAdj()) {
        if(edge->getDest() == d) e = edge;
    }
    if (e == nullptr) {
        std::cout << RED << "Error: The Pipe does not exist." << WHITE << std::endl;
        return;
    }

    Graph graph = network;
    network.removeEdge(v, d);
    network.edmondsKarp();
    std::vector<Vertex *> affectedCities;
    std::vector<Vertex *> affectedReservoirs;
    for (auto c: network.getCityVertexes()) {
        if (c.second->getAdj()[0]->getFlow() != graph.getCityVertexes().at(c.second->getTypeId())->getAdj()[0]->getFlow()) {
            affectedCities.push_back(c.second);
        }
    }
    for (auto r: network.getReservoirVertexes()) {
        if (r.second->getIncoming()[0]->getFlow() != graph.getReservoirVertexes().at(r.second->getTypeId())->getIncoming()[0]->getFlow()) {
            affectedReservoirs.push_back(r.second);
        }
    }

    printAffected(graph, affectedCities, affectedReservoirs);
}

void Runtime::restore(std::vector<std::string> args) {
    if (args.size() != 1) {
        std::cout << RED << "Error: expected no arguments." << ANSI_RESET << std::endl;
        return;
    }
    network.restore();
    network.edmondsKarp();
}

void Runtime::showDependency(std::vector<std::string> args) {
    if (!network.getRemovedVertexes().empty() or !network.getRemovedEdges().empty()) {
        std::cout << RED << "Warning:" << WHITE << "Please, restore the graph before removing anything else." << std::endl;
        return;
    }

    if (args.size() != 2) {
        std::cout << RED << "Error: expected 1 argument." << ANSI_RESET << std::endl;
        return;
    }

    unsigned int id;
    Vertex * v;
    try {
        id = stoul(args[1]);
        v = network.getCityVertexes().at(id);
    } catch (...) {
        std::cout << RED << "Error: " << args[1] << " is not a valid City id." << WHITE << std::endl;
        return;
    }

    if (v->getDependency().empty()) {
        std::cout << GREEN << "The City of " << v->getCity() << " with id " << id << " does not depend on any Pipeline."
                  << WHITE << std::endl << std::endl;
        return;
    }

    std::cout << YELLOW << "The City of " << v->getCity() << " with id " << id << " depends on these Pipelines:"
              << WHITE << std::endl;
    for (auto d: v->getDependency()) {
        std::cout << d.first->getOrig()->getCode() << " --> " << d.first->getDest()->getCode() << ":" << std::endl
                  << "     Flow before removal of Pipe: " << v->getAdj()[0]->getFlow() << std::endl
                  << "     Flow after removal of Pipe: " << v->getAdj()[0]->getFlow() - d.second << std::endl
                  << "     Difference: " << d.second << std::endl << std::endl;
    }
}
