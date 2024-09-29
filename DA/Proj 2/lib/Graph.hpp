/**
 * @file Graph.hpp
 * @brief Declaration of class Graph
 * @author G17_5
 * @date 17/05/2024
 */

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <unordered_map>
#include <queue>
#include <sstream>
#include <math.h>
#include "Auxil.hpp"
#include "Macros.hpp"
#include "Vertex.hpp"

//! Water Network
class Graph {
  private:
    std::vector<Vertex*> vertexSet;                                   /*!< Set of vertexes */
    std::unordered_map<unsigned,Vertex*> vertexMap;                   /*!< Unordered map of vertex ID to own vertex */

    /**
     * @brief Recursive function to find a path in the MST
     *
     * @details This is a tweaked version of the pre-order walk of the MST used in the triangular inequality 2-approximation algorithm. When the algorithm gets stuck in a vertex that can't go further in the pre-order walk, the algorithm goes back and leaves that vertex behind. Thus, if in the future we can visit it, we will.
     *
     * @param Vertex* v : current vertex
     * @param std::vector<Vertex*>& path : minimal path found by the algorithm
     * @param double cost :
     * @param unsigned int leftBehindCounter : Counter of the left behind vertexes
     * @return double : 0 if succeeded to find a path, -1 if not and -2 if the vertex is to be left behind
     * @note Time Complexity : O(V + E), Space Complexity : O(V)
     */
    int findPath(Vertex *v, std::vector<Vertex *> &path, double &cost, unsigned int &leftBehindCounter);
  public:
    /**
     * @brief Default constructor
     * @note Time Complexity : O(1), Space Complexity : O(1)
     */
    Graph();

    /**
     * @brief Returns a Vertex if present, using an ID to search
     * @param unsigned int id : the ID of the Vertex to look for
     * @return Vertex* : nullptr if not found
     * @note Does not change attributes
     * @note Time Complexity : O(V), Space Complexity : O(1)
     */
    Vertex* findVertex(unsigned int id) const;

    /**
     * @brief Returns an Edge if present, using two IDs to search
     * @param Vertex* src : origin
     * @param Vertex* dst : destination
     * @return Edge* : nullptr if not found
     * @note Time Complexity : O(V + n), n being the number of adjacent edges of src, Space Complexity : O(1)
     */
    Edge* findEdge(unsigned int source, unsigned int dest);

    /**
     * @brief Adds a Vertex
     * @param Vertex* v : the Vertex to add
     * @return void
     * @note Time Complexity : O(1), Space Complexity : O(1)
     */
    void addVertex(Vertex* v);

    /**
     * @brief Removes a Vertex, using an ID to search
     * @param unsigned int id : the ID of the Vertex to remove
     * @return bool : true if successful
     * @note Time Complexity : O(V + E), Space Complexity : O(1)
     */
    bool removeVertex(unsigned int id);

    /**
     * @brief Adds an Edge
     * @param unsigned int source : ID of origin
     * @param unsigned int dest : ID of destination
     * @param double w : length of edge
     * @return Edge* : the own edge, or nullptr if not added
     * @note Time Complexity : O(V + E), Space Complexity : O(1)
     */
    Edge* addEdge(unsigned int source, unsigned int dest, double l);

    /**
     * @brief Removes an Edge
     * @param unsigned int source : ID of source
     * @param unsigned int dest : ID of destination
     * @return bool : true if successful
     * @note Time Complexity : O(V + n) n being the number of adjacent edges of src, Space Complexity : O(1)
     */
    bool removeEdge(unsigned int source, unsigned int dest);

    /**
     * @brief Returns the vector of Vertexes
     * @return const std::vector<Vertex*>& : vector of vertexes
     * @note Does not change attributes
     * @note Time Complexity : O(1), Space Complexity : O(1)
     */
    const std::vector<Vertex*> &getVertexSet() const;

    /**
     * @brief Backtracks through the current path if its length surpasses the current minimum
     * @param unsigned int source : where to start the algorithm
     * @param std::vector<Vertex*>& path : minimum Hameltonian cycle
     * @return double : length of the path
     * @note Time Complexity: O(V!), Space Complexity: O(V)
     */
    double backtrack(unsigned int source, std::vector<Vertex*>& path);

    /**
     * @brief Computes a Minimal Spanning Tree using the Prim's algorithm
     * @param unsigned int source : where to start the tree
     * @return void
     * @note Time Complexity: O(V * log V + E), Space Complexity: O(1)
     */
    void primMST(unsigned int source);

    /**
     * @brief Executes the Bellman-Held-Karp String Variation on the graph to compute a solution to the Travelling Salesperson Problem
     * @brief The String Variation was made by me (Lucas) as the original variation uses too much memory
     * @brief This variation is slower due to the constant find-erase executed - however, the memory usage is considerably smaller
     * @brief This version, as well as the original one, are only viable for small graphs (|V| < 18, depending on machine specifications)
     * @param unsigned int source : where to start the algorithm
     * @return double : the length of the path
     * @note Time Complexity: O(2^V * V^2), Space Complexity: O(1) (after the function ends)
     */
    double bellmanHeldKarpString(unsigned int source);

    /**
     * @brief Dynamic Programming approach to the Travelling Salesperson Problem - is the optimal algorithm with the lowest complexity found yet, still exponential though
     * @brief Due to its nature, this algorithm uses a lot of memory. Use it only for small graphs and if you have enough remaining resources
     * @param unsigned int source : where to start the algorithm
     * @return double : the length of the path
     * @note Time Complexity: O(2^V * V^3) (due to the map, log2(2^V) = V), Space Complexity: O(1) (after the function ends)
     */
    double bellmanHeldKarp(unsigned int source);

    /**
     * @brief For each vertex, advances on the edge with the shortest length - greedy algorithm
     * @param unsigned int source : where to start the algorithm
     * @param std::vector<Vertex*>& path : minimal path found by the algorithm
     * @return double : length of the minimal path found by the algorithm
     * @note Time Complexity: O(V * (V + E)), Space Complexity: O(V)
     */
    double nearestNeighbour(unsigned int source, std::vector<Vertex*>& path);
    
    /**
     * @brief For graphs with respect Triangle Inequality, computes a Prim Minimal Spanning Tree and then traverses it
     * @param unsigned int source : where to start the algorithm
     * @param std::vector<Vertex*>& path : minimal path found by the algorithm
     * @return double : length of the minimal path found by the algorithm
     * @note Time Complexity: O(V * logV + E), Space Complexity: O(V)
     */
    double triangleInequality(unsigned int source, std::vector<Vertex*>& path);

    /**
     * @brief Tweaked version of the triangular inequality 2-approximation algorithm to work on not fully connected real world graphs
     *
     * @details This algorithm computes an MST of the graph. Then, it uses the function Graph::findPath() to try to find the path.
     *
     * @param unsigned int source : where to start the algorithm
     * @param std::vector<Vertex*>& path : minimal path found by the algorithm
     * @return double : length of the minimal path found by the algorithm
     * @note Time Complexity: O(V * logV + E), Space Complexity: O(V)
     */
    double realWorldTSP(unsigned int source, std::vector<Vertex *> &path);

    /**
     * @brief Returns attributes modified by certain algorithms to their normal values
     * @return void
     * @note Time Complexity: O(V), Space Complexity: O(1)
     */
    void restore();

    /**
     * @brief Ensures the graph is fully connected, meaning every vertex has a connection to every other vertex
     * @param bool infinite = false : whether to set the new edges with infinite length or with length calculated from the Vertex geographic position
     * @return void
     * @note Time Complexity: O(V^2), Space Complexity: O(1)
     */
    void ensureFullyConnected(bool infinite = false);

    /**
     * @brief Destroys everything
     * @note Time Complexity : O(V + E), Space Complexity : O(1)
     */
    ~Graph();
};

#endif // GRAPH_HPP
