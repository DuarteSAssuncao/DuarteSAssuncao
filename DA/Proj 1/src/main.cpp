/**
 * @file main.cpp
 * @author G17_5
 * @brief Main file for compilation. Initializes the project
 * @date 05/03/2024
*/

#include <iostream>
#include <cstring>

#include "../lib/Graph.hpp"
#include "../lib/Parser.hpp"
#include "../lib/Tests.hpp"
#include "../lib/Runtime.hpp"


//! If you want to execute edmondsKarp() followed by fordFulkerson(), make sure to call reset() between the two functions
int main(int argc, char *argv[]) {
    if (argc != 1 && !strcmp(argv[1], "-t")) {
        Graph madeira = parse("csv/Cities_Madeira.csv", "csv/Pipes_Madeira.csv", "csv/Reservoirs_Madeira.csv", "csv/Stations_Madeira.csv");
        madeira.fordFulkerson();  // max-flow: 24163
        madeira.calculateDependency();
        Runtime rt = Runtime(&madeira);
        rt.run();
    } else {
        Graph network = parse("csv/Cities.csv", "csv/Pipes.csv", "csv/Reservoirs.csv", "csv/Stations.csv");
        network.edmondsKarp();    // max-flow: 24163
        network.calculateDependency();
        Runtime rt = Runtime(&network);
        rt.run();
    }
    return 0;
}
