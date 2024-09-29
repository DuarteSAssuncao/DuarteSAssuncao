/**
* @file Runtime.hpp
* @brief Definition of class Runtime
* @author G17_5
* @date 17/05/2024
*/

#ifndef RUNTIME_HPP
#define RUNTIME_HPP

#include "Graph.hpp"
#include "Macros.hpp"
#include <chrono>

//! Runtime
class Runtime {
  private:
    Graph *network;
    std::chrono::steady_clock::time_point begin;
    std::chrono::steady_clock::time_point end;

  protected:
    /**
     * @brief Reads the command written by the user and separates it into a vector of string arguments
     * @return std::vector<std::string> : vector with the command (first position) and its arguments
     * @note Time Complexity: O(n), Space Complexity: O(1)
     */
    std::vector<std::string> readCommand();

    /**
     * @brief Prints a detailed list of all the commands.
     * @return void
     * @note Time Complexity: O(1), Space Complexity: O(1)
     */
    static void help();

  public:
    /**
     * @brief Runs the program
     * @return void
     * @note Time Complexity: O(V!) at worst, Space Complexity: O(1)
     */
    void run();

    /**
     * @brief Loads and parses the given files
     * @param std::vector<std::string>& args : arguments provided by the user
     * @return void
     * @note Time Complexity: O(V + E), Space Complexity: O(V + E)
     */
    void load(std::vector<std::string>& args);

    /**
     * @brief Executes the Backtracking algorithm: Graph::backtrack()
     * @param std::vector<std::string>& args : arguments provided by the user
     * @return void
     * @note Time Complexity: (V!), Space Complexity: O(V)
     */
    void backtrack(std::vector<std::string>& args);

    /**
     * @brief Executes the Triangle Inequality algorithm: Graph::triangleInequality()
     * @param std::vector<std::string>& args : arguments provided by the user
     * @return void
     * @note Time Complexity: O(V * logV + E), Space Complexity: O(V)
     */
    void tineq(std::vector<std::string>& args);

    /**
     * @brief Executes the Bellman-Held-Karp algorithm: Graph::bellmanHeldKarp()
     * @param std::vector<std::string>& args : arguments provided by the user
     * @return void
     * @note Time Complexity: O(2^V * V^3), Space Complexity: O(1)
     */
    void bhk (std::vector<std::string>& args);

    /**
     * @brief Executes the Bellman-Held-Karp String Variation algorithm: Graph::bellmanHeldKarpString()
     * @param std::vector<std::string>& args : arguments provided by the user
     * @return void
     * @note Time Complexity: O(2^V * V^2), Space Complexity: O(1)
     */
    void bhks (std::vector<std::string>& args);

    /**
     * @brief Executes the Nearest Neighbour algorithm: Graph::nearestNeighbour()
     * @param std::vector<std::string>& args : arguments provided by the user
     * @return void
     * @note Time Complexity: O(V * (V + E)), Space Complexity: O(V)
     */
    void near(std::vector<std::string>& args);

    /**
     * @brief Executes the Real World algorithm: Graph::realWorldTSP()
     * @param std::vector<std::string>& args : arguments provided by the user
     * @return void
     * @note Time Complexity: O(V * logV + E), Space Complexity: O(V)
     */
    void realWorld(std::vector<std::string>& args);

    /**
     * @brief Constructor
     * @note Time Complexity: O(1), Space Complexity: O(1)
     */
    Runtime();

    /**
     * @brief Destructor
     * @note Time Complexity: O(V + E), Space Complexity: O(1)
     */
    ~Runtime();
};

#endif // RUNTIME_HPP
