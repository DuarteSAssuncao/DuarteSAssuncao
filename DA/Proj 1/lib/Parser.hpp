/**
* @file Parser.hpp
* @brief Declaration of Parser function and its auxiliary functions
* @author G17_5
* @date 17/03/2024
*/

#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include "Macros.hpp"
#include "Graph.hpp"

/**
* @brief Checks if a file with the given name exists
* @param const std::string filename: name of the file
* @param std::fstream& In: file parser
* @return bool: true if the file is valid
* @note Time Complexity: O(1), Space Complexity: O(1);
*/
bool check_file(const std::string filename, std::fstream& In);

/**
* @brief Parses all files and builds the graph
* @param const std::string cities_csv: filename with the cities' data
* @param const std::string pipes_csv: filename with the pipes' data
* @param const std::string reservoirs_csv: filename with the reservoirs' data
* @param const std::string stations_csv: filename with the stations' data
* @return Graph: water network
* @note Time Complexity: O(V + E), Space Complexity: O(V + E);
*/
Graph parse(const std::string cities_csv, const std::string pipes_csv, const std::string reservoirs_csv, const std::string stations_csv);

/**
* @brief Parses the cities
* @param Graph& network: graph being built
* @param const std::string file: file with the cities' data
* @return void
* @note Time Complexity: O(C), Space Complexity: O(1);
*/
void parseCities(Graph &network, const std::string file);

/**
* @brief Parses the pipes
* @param Graph& network: graph being built
* @param const std::string file: file with the pipes' data
* @return void
* @note Time Complexity: O(P), Space Complexity: O(1);
*/
void parsePipes(Graph &network, const std::string file);

/**
* @brief Parses the reservoirs
* @param Graph& network: graph being built
* @param const std::string file: file with the reservoirs' data
* @return void
* @note Time Complexity: O(R), Space Complexity: O(1);
*/
void parseReservoirs(Graph &network, const std::string file);

/**
* @brief Parses the stations
* @param Graph& network: graph being built
* @param const std::string file: file with the stations' data
* @return void
* @note Time Complexity: O(s), Space Complexity: O(1);
*/
void parseStations(Graph &network, const std::string file);

#endif // PARSER_HPP
