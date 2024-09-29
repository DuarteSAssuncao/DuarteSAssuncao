/**
* @file Parser.hpp
* @brief Declaration of Parser function and its auxiliary functions
* @author G17_5
* @date 17/05/2024
*/

#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <unordered_map>
#include "Macros.hpp"
#include "Graph.hpp"

/**
* @brief Checks if a file with the given name exists
* @param const std::string& filename : name of the file
* @param std::ifstream& In : file parser
* @return bool : whether the file is valid
* @note Time Complexity : O(1), Space Complexity : O(1);
*/
bool check_file(const std::string& filename, std::ifstream& In);

/**
* @brief Parses the given file(s) and builds the graph
* @param Graph& result : the graph being built
* @param const std::string& edges_csv : file with the edges' data
* @param const std::string& vertexes_csv = "" : file with the vertexes' data
* @return void
* @note Time Complexity : O(V + E), Space Complexity : O(V + E);
*/
void parse(Graph &result, const std::string& edges_csv, const std::string& vertexes_csv = "");

/**
* @brief Parses the Vertexes
* @param Graph& network : graph being built
* @param const std::string& file : file with the vertexes' data
* @param unsigned int limit : how many vertexes to parse
* @return void
* @note Time Complexity : O(limit), Space Complexity : O(limit);
*/
void parseVertexes(Graph &network, const std::string& file, unsigned int limit);


/**
 * @brief Parses the Edges
 * @param Graph& network : graph being built
 * @param const std::string& file : file with the edges' data
 * @return void
 * @note Time Complexity : O(E), Space Complexity : O(E);
 */
void parseEdges(Graph &network, const std::string& file);

/**
 * @brief Parses Vertexes and Edges for the Toy Graphs
 * @param Graph& network : graph being built
 * @param const std::string& file : file with the edges' and vertexes' data
 * @return void
 * @note Time Complexity : O(E), Space Complexity : O(V + E);
 */
void parseVertexesAndEdges(Graph &network, const std::string& file);

#endif // PARSER_HPP
