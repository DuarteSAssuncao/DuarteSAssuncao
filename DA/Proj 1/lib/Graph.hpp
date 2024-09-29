/**
 * @file Graph.hpp
 * @brief Declaration of class Graph
 * @author G17_5
 * @date 09/03/2024
 */

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <queue>
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <cfloat>
#include "Macros.hpp"
#include "Vertex.hpp"

//! Water Network
class Graph {
private:
    Vertex *source = new Vertex(SOURCE, 0, "", "", "", 0);          /*!< Connected to all Reservoirs */
    Vertex *sink = new Vertex(SINK, 0, "", "", "", 0);              /*!< All cities are connected to this Vertex */

    std::vector<Vertex *> vertexSet;                                /*!< Set of vertexes */

    std::unordered_map<unsigned int, Vertex *> cityVertexes;        /*!< Map to find cities easily */
    std::unordered_map<unsigned int, Vertex *> reservoirVertexes;   /*!< Map to find reservoirs easily */
    std::unordered_map<unsigned int, Vertex *> stationVertexes;     /*!< Map to find pumping stations easily */

    std::vector<Vertex *> removedVertexes;                          /*!< Vector to keep removed vertexes */
    std::vector<Edge *> removedEdges;                               /*!< Vector to keep remove edges */ 
public:
    /**
     * @brief Default constructor
     * @note Time Complexity: O(1), Space Complexity: O(1)
     */
    Graph();
    
    /**
     * @brief Deep copy constructor
     * @param const Graph& other: graph to copy
     * @note Time Complexity: O(1), Space Complexity: O(1)
     */
    Graph(const Graph &other);

    /**
     * @brief Returns a Vertex if present. Uses an ID to search
     * @param unsigned int id: the ID of the Vertex to look for
     * @return Vertex*: nullptr if not found
     * @note Does not change attributes
     * @note Time Complexity: O(V), Space Complexity: O(1)
     */
    Vertex *findVertex(unsigned int id) const;

    /**
     * @brief Returns a Vertex if present. Uses a code and unordered maps to search
     * @param std::string& code: the code of the Vertex
     * @return Vertex* : nullptr if not found
     * @note Time Complexity: O(1), Space Complexity: O(1)
     */
    Vertex *findVertex(const std::string &code);

    /**
     * @brief Returns an Edge if present
     * @param Vertex* src: origin
     * @param Vertex* dst: destination
     * @return Edge*: nullptr if not found
     * @note Time Complexity: O(n), n being the number of adjacent edges of src, Space Complexity: O(1)
     */
    Edge *findEdge(Vertex *src, Vertex *dst);

    /**
     * @brief Adds a Vertex
     * @param Vertex* v: the Vertex to add
     * @return bool: true if successful
     * @note Time Complexity: O(1), Space Complexity: O(1)
     */
    bool addVertex(Vertex *v);

    /**
     * @brief Removes a Vertex. Uses and ID and optionally iterations
     * @param unsigned int id: the ID of the Vertex to remove
     * @param (Optional) unsigned int* iterations = nullptr: number of iterations
     * @return bool: true if successful
     * @note Auxiliary function
     * @note Time Complexity: O(1), Space Complexity: O(1)
     */
    bool removeVertex(unsigned int id, unsigned *iterations = nullptr);

    /**
     * @brief Reduces the flow from a vertex to another by an amount smaller or equal to the value provided.
     * @param Vertex* src: origin
     * @param Vertex* dst: destination
     * @param double limit: the maximum flow that can be reduced
     * @return unsigned : number of BFSs
     * @note The network's flow may become invalid if src != getSource() && dst != getSink()
     * @note Does not change attributes
     * @note Time Complexity: O(V * E²), Space Complexity: O(V)
     */
    unsigned reduceFlow(Vertex *src, Vertex *dst, double limit) const;

    /**
     * @brief Adds an Edge
     * @param unsigned int source: ID of origin
     * @param unsigned int dest: ID of destination
     * @param double w: capacity of edge
     * @return bool: true if successful
     * @note Time Complexity: O(V + E), Space Complexity: O(1)
     */
    Edge * addEdge(unsigned int source, unsigned int dest, double w);

    /**
     * @brief Removes an Edge
     * @param Vertex* src: origin
     * @param Vertex* dest: destination
     * @param (Optional) unsigned* iterations = nullptr: number of iterations
     * @return bool: true if successful
     * @note Auxiliary functino
     * @note Time Complexity: O(n) n being the number of adjacent edges of src, Space Complexity: O(1)
     */
    bool removeEdge(Vertex *src, Vertex *dest, unsigned *iterations = nullptr);

    /**
     * @brief Returns the vector of Vertexes
     * @return const std::vector<Vertex*>&: vector of vertexes
     * @note Does not change attributes
     * @note Time Complexity: O(1), Space Complexity: O(1)
     */
    const std::vector<Vertex *> &getVertexSet() const;

    /**
     * @brief Returns the Source
     * @return Vertex*: Source
     * @note Does not change attributes
     * @note Time Complexity: O(1), Space Complexity: O(1)
     */
    Vertex *getSource() const;

    /**
     * @brief Returns the Sink
     * @return Vertex*: Sink
     * @note Does not change attributes
     * @note Time Complexity: O(1), Space Complexity: O(1)
     */
    Vertex *getSink() const;

    /**
     * @brief Returns the total flow
     * @return double: total flow
     * @note Does not change attributes
     * @note Time Complexity: O(V + E), Space Complexity: O(1)
     */
    double getFlow() const;

    /**
     * @brief Returns the flow coming out of the Source
     * @return double: flow coming from Source
     * @note Does not change attributes
     * @note Time Complexity: O(V + E), Space Complexity: O(1)
     */
    double getFlowFromSource() const;

    /**
     * @brief Returns the unordered map of cities
     * @return const std::unordered_map<unsigned int, Vertex*>&: map of cities
     * @note Does not change attributes
     * @note Time Complexity: O(1), Space Complexity: O(1)
     */
    const std::unordered_map<unsigned int, Vertex *> &getCityVertexes() const;

    /**
     * @brief Returns the unordered map of reservoirs
     * @return const std::unordered_map<unsigned int, Vertex*>&: map of reservoirs
     * @note Does not change attributes
     * @note Time Complexity: O(1), Space Complexity: O(1)
     */
    const std::unordered_map<unsigned int, Vertex *> &getReservoirVertexes() const;

    /**
     * @brief Returns the unordered map of stations
     * @return const std::unordered_map<unsigned int, Vertex*>&: map of stations
     * @note Does not change attributes
     * @note Time Complexity: O(1), Space Complexity: O(1)
     */
    const std::unordered_map<unsigned int, Vertex *> &getStationVertexes() const;

    /**
     * @brief Returns the vector of removed vertexes
     * @return const std::vector<Vertex*>&: vector of removed vertexes
     * @note Does not change attributes
     * @note Time Complexity: O(1), Space Complexity: O(1)
     */
    const std::vector<Vertex *> &getRemovedVertexes() const;

    /**
     * @brief Returns the vector of removed edges
     * @return const std::vector<Vertex*>&: vector of removed edges
     * @note Does not change attributes
     * @note Time Complexity: O(1), Space Complexity: O(1)
     */
    const std::vector<Edge *> &getRemovedEdges() const;

    /**
     * @brief Sets all vertex as unvisited
     * @return void
     * @note Does not change attributes
     * @note Time Complexity: O(V), Space Complexity: O(1)
     */
    void setAllVisitedFalse() const;

    /**
     * @brief Calculates the maximum flow
     * @return unsigned: maximum flow
     * @note Time Complexity: O(V * E²), Space Complexity: O(1)
     */
    unsigned edmondsKarp();

    /**
     * @brief Computes augmenting paths
     * @param Vertex* v: current Vertex
     * @param std::vector<Edge*>& toIncreaseFlow: set of edges whose flow must be increased
     * @param std::vector<Edge*>& toDecreaseFlow: set of edges whose flow must be decreased
     * @param double& flow: flow of the path
     * @param bool& found: if a path to the Sink was found
     * @return void
     * @note Time Complexity: O(V * E), Space Complexity: O(V)
     */
    void recursiveAugmentingPath(
        Vertex *v,
        std::vector<Edge *> &toIncreaseFlow,
        std::vector<Edge *> &toDecreaseFlow,
        double &flow,
        bool &found
    );

    /**
     * @brief Calculates maximum flow
     * @return double: maximum flow
     * @note Time Complexity: O(V * E²), Space Complexity: O(1)
     */
    double fordFulkerson();
  
    /**
     * @brief Resets only the flow
     * @return void
     * @note Time Complexity: O(V + E), Space Complexity: O(1)
     */
    void resetFlow();

    /**
     * @brief Resets all attributes modified by maximum flow algorithms
     * @return void
     * @note Time Complexity: O(V + E), Space Complexity: O(1)
     */
    void reset();

    /**
     * @brief Restores all removed vertexes and edges
     * @return void
     * @note Time Complexity: O(V + E), Space Complexity: O(1)
     */
    void restore();

    /**
     * @brief Fills the dependency vector of every city
     * @return void
     * @note Tries to remove every pipe and executes midway maximum flow algorithm
     * @note Finds out which cities were affected by each pipe removal
     * @note Time Complexity: O(V * E³), Space Complexity: O(1)
     */
    void calculateDependency();

    /**
     * @brief Destroys everything
     * @note Time Complexity: O(V + E), Space Complexity: O(1)
     */
    ~Graph();
};

#endif // GRAPH_HPP
