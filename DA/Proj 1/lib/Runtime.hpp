/**
* @file Runtime.hpp
* @brief Definition of class Runtime
* @author G17_5
* @date 17/03/2024
*/

#ifndef RUNTIME_HPP
#define RUNTIME_HPP

#include "Graph.hpp"
#include "Macros.hpp"

//! Runtime
class Runtime {
private:
    Graph network;

    /**
     * @brief Prints the Cities and Reservoirs that were affected by the removal of a vertex or edge
     * @param Graph& graph: Original graph before the removal
     * @param const std::vector<Vertex*>& affectedCities: vector of affected Cities
     * @param const std::vector<Vertex*>& affectedReservoirs: vector of affected Reservoirs
     * @return void
     * @note Auxiliary function for remove command
     * @note Time Complexity: O(v), Space Complexity: O(1)
     */
    void printAffected(Graph &graph, const std::vector<Vertex *>& affectedCities, const std::vector<Vertex *>& affectedReservoirs);

protected:
    /**
     * @brief Reads the command written by the user and separates it into a vector of string arguments
     * @return std::vector<std::string>: vector with the command (first position) and its arguments.
     * @note Time Complexity: O(n), Space Complexity: O(1)
     */
    std::vector<std::string> readCommand();

    /**
     * @brief Prints a detailed list of all the commands.
     * @param std::vector<std::string> args: arguments
     * @return void
     * @note Time Complexity: O(1), Space Complexity: O(1)
     */
    void help(std::vector<std::string> args);

    /**
     * @brief Displays the city with that ID, or all of them in case the flag -all is used.
     * @param std::vector<std::string> args: arguments
     * @return void
     * @note Time Complexity: O(1), or O(C * log C) if -all is used, Space Complexity: O(1)
     */
    void displayCity(std::vector<std::string> args);

    /**
     * @brief Displays the reservoir with that ID, or all of them in case the flag -all is used
     * @param std::vector<std::string> args: arguments
     * @return void
     * @note Time Complexity: O(1), or O(R * log R) in case -all is used, Space Complexity: O(1)
     */
    void displayReservoir(std::vector<std::string> args);

    /**
     * @brief Displays the station with that ID, or all of them in case the flag -all is used
     * @param std::vector<std::string> args: arguments
     * @return void
     * @note Time Complexity: O(1), or O(S * log S) in case -all is used, Space Complexity: O(1)
     */
    void displayStation(std::vector<std::string> args);

    /**
     * @brief Displays the cities whose water demand is not fulfilled by the network
     * @param std::vector<std::string> args: arguments (only empty is accepted)
     * @return void
     * @note Time Complexity: O(C), Space Complexity: O(1)
     */
    void needyCities(std::vector<std::string> args);

    /**
     * @brief Removes either a city, reservoir, or station and prints the cities/reservoirs affected
     * @param std::vector<std::string> args: arguments
     * @return void
     * @note This algorithm doesn't go through all the augmenting paths, thus being generally more efficient than Edmonds-Karp
     * @note Time Complexity: O(V * E²), Space Complexity: O(1)
     */
    void remove(std::vector<std::string> args);

    /**
     * @brief Removes a pipe and prints the cities/reservoirs affected
     * @param std::vector<std::string> args: arguments
     * @return void
     * @note This algorithm doesn't go through all the augmenting paths, thus being generally more efficient than Edmonds-Karp
     * @note Time Complexity: O(V * E²), Space Complexity: O(1)
     */
    void removePipe(std::vector<std::string> args);

    /**
     * @brief Undoes the previous removal
     * @param std::vector<std::string> args: arguments (only empty is accepted)
     * @return void
     * @note Runs midway Edmonds-Karp, considering the current flow of the graph and trying to increase it
     * @note This algorithm doesn't go through all the augmenting paths, thus being generally more efficient than scratch Edmonds-Karp
     * @note Time Complexity: O(V * E²), Space Complexity: O(1)
     */
    void restore(std::vector<std::string> args);

    /**
     * @brief For a given city, shows which pipes, if ruptured, would affect the amount of water reaching the city
     * @param std::vector<std::string> args: arguments
     * @return void
     * @note Time Complexity: O(n), where n is the number of Pipes that the given city depends on, Space Complexity: O(1)
     * @note Although the complexity of this command is linear, it depends on the method Graph::calculateDependency(), which has complexity of O(V * E³) and is executed in the beginning of the program
     */
    void showDependency(std::vector<std::string> args);

    /**
     * @brief Prints statistics about the pipes
     * @param const Graph& g: graph
     * @return void
     * @note This function is static
     * @note Time Complexity: O(E * log E + V), Space Complexity: O(1)
     */
    static void print_pipes_statistics(const Graph &g);

public:
    /**
     * @brief Runs the program
     * @return void
     * @note Time Complexity: O(V * E³) at worst, Space Complexity: O(1)
     */
    void run();

    /**
     * @brief Constructor with the network
     * @param Graph* graph: water network
     * @note Time Complexity: O(1), Space Complexity: O(1)
     */
    Runtime(Graph *graph);
};

#endif // RUNTIME_HPP
