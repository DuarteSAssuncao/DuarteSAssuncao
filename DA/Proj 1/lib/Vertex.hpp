/**
* @file Vertex.hpp
* @brief Declaration of class Vertex
* @author G17_5
* @date 09/03/2024
*/

#ifndef VERTEX_HPP
#define VERTEX_HPP

class Edge;

#include <vector>
#include <string>
#include "Edge.hpp"

enum node_type {
    CITY,           // The id of the vertex is the id of the City with the digit 1 at the end
    RESERVOIR,      // The id of the vertex is the id of the Reservoir with the digit 2 at the end
    STATION,        // The id of the vertex is the id of the Station with the digit 3 at the end
    SOURCE,         // The id of the Source is 0
    SINK            // The id of the Sink is 0
};

//! Cities, Reservoirs and Stations
class Vertex {
private:
    double dist = 0;                            /*!< Auxiliary field for some algorithms */
    bool visited = false;                       /*!< Auxiliary field for some algorithms */
    Edge *path = nullptr;                       /*!< On a path, previous edge */

    std::vector<Edge *> adj;                    /*!< Outgoing edges */
    std::vector<Edge *> incoming;               /*!< Incoming edges */

    std::vector<std::pair<Edge *, double>> dependency; /*!< Pipes essential to a city and the deficit of water supply caused by its removal */

    node_type type;                             /*!< The vertex can be a City, a pumping Station or a Reservoir */
    unsigned int id;                            /*!< Each Vertex has an	unique ID */
    std::string reservoir = "";                 /*!< Reservoir name in case it is a reservoir */
    std::string municipality = "";              /*!< Municipality of the reservoir */
    std::string city = "";                      /*!< City name in case it is a city */
    unsigned int population = 0;                /*!< Population of the city */
public:
    /**
     * @brief Constructor with a lot of attributes
     * @param node_type type: specifies the type of the Vertex
     * @param unsigned int id: unique identifier
     * @param const std::string reservoir = "": if a reservoir, its name
     * @param const std::string municipality = "": if a reservoir, its municipality
     * @param const std::string city = "": if a city, its name
     * @param unsigned int population = 0: if a city, its population
     * @note The city demand is present in its edge to the Sink
     * @note Time Complexity: O(1), Space Complexity: O(1)
     */
    Vertex(node_type type,
           unsigned int id,
           const std::string reservoir = "",
           const std::string municipality = "",
           const std::string city = "",
           unsigned int population = 0);

    /**
     * @brief Returns the distance, a.k.a. the maximum flow until that point in the path
     * @return double: maximum flow until that point in the path
     * @note Does not change attributes
     * @note Time Complexity: O(1), Space Complexity: O(1)
     */
    double getDist() const;

    /**
     * @brief Returns whether the vertex was visited
     * @return bool: whether the vertex was visited
     * @note Does not change attributes
     * @note Time Complexity: O(1), Space Complexity: O(1)
     */
    bool isVisited() const;

    /**
     * @brief Returns the previous edge in the path
     * @return Edge*: previous edge in the path
     * @note Does not change attributes
     * @note Time Complexity: O(1), Space Complexity: O(1)
     */
    Edge *getPath() const;

    /**
     * @brief Returns the outgoing edges
     * @return std::vector<Edge*>&: vector of outgoing edges
     * @note Time Complexity: O(1), Space Complexity: O(1)
     */
    std::vector<Edge *> &getAdj();

    /**
     * @brief Returns the incoming edges
     * @return std::vector<Edge*>&: vector of incoming edges
     * @note Time Complexity: O(1), Space Complexity: O(1)
     */
    std::vector<Edge *> &getIncoming();

    /**
     * @brief Returns the outgoing edges
     * @return const std::vector<Edge*>&: vector of outgoing edges
     * @note Does not change attributes
     * @note Does not throw exceptions
     * @note Time Complexity: O(1), Space Complexity: O(1)
     */
    const std::vector<Edge *> &getAdj() const noexcept;
    /**
     * @brief Returns the incoming edges
     * @return const std::vector<Edge*>&: vector of incoming edges
     * @note Does not change attributes
     * @note Does not throw exceptions
     * @note Time Complexity: O(1), Space Complexity: O(1)
     */
    const std::vector<Edge *> &getIncoming() const noexcept;

    /**
     * @brief Returns the dependency vector
     * @return const std::vector<std::pair<Edge*, double>>&: dependency vector
     * @note Does not change attributes
     * @note Time Complexity: O(1), Space Complexity: O(1)
     */
    const std::vector<std::pair<Edge *, double>> &getDependency() const;

    /**
     * @brief Adds an edge to the dependency vector
     * @param Edge* e: pipe essential to the city
     * @param double value: value of the pipe
     * @return void
     * @note Time Complexity: O(1), Space Complexity: O(1)
     */
    void addDependency(Edge *e, double value);

    /**
     * @brief Sets the distance, a.k.a. the maximum flow until that point in the path
     * @param double dist: updated maximum flow
     * @return void
     * @note Time Complexity: O(1), Space Complexity: O(1)
     */
    void setDist(double dist);

    /**
     * @brief Sets whether the vertex was visited
     * @param bool visited: whether the vertex was visited
     * @return void
     * @note Time Complexity: O(1), Space Complexity: O(1)
     */
    void setVisited(bool visited);

    /**
     * @brief Sets the previous edge in the path
     * @param Edge* path: previous edge in the path
     * @return void
     * @note Time Complexity: O(1), Space Complexity: O(1)
     */
    void setPath(Edge *path);

    /**
     * @brief Adds an edge
     * @param Vertex* dest: destination
     * @param double w: capacity of the edge
     * @return Edge* : nullptr if not added
     * @note Time Complexity: O(1), Space Complexity: O(1)
     */
    Edge *addEdge(Vertex *dest, double w);

    /**
     * @brief Removes an edge
     * @param Vertex* v: destination
     * @return Edge*: nullptr if the edge does not exist
     * @note Time Complexity: O(E), Space Complexity: O(1)
     */
    Edge *removeEdge(Vertex *v);

    /**
     * @brief Returns the ID
     * @return unsigned int: ID of the Vertex
     * @note Does not change attributes
     * @note Time Complexity: O(1), Space Complexity: O(1)
     */
    unsigned int getId() const;

    /**
     * @brief Returns the type ID
     * @return unsigned int: type ID of the Vertex
     * @note Does not change attributes
     * @note Time Complexity: O(1), Space Complexity: O(1)
     */
    unsigned int getTypeId() const;

    /**
     * @brief Returns the code
     * @return std::string: code of the Vertex
     * @note Does not change attributes
     * @note Time Complexity: O(1), Space Complexity: O(1)
     */
    std::string getCode() const;

    /**
     * @brief Returns the type
     * @return node_type: type of the Vertex
     * @note Does not change attributes
     * @note Time Complexity: O(1), Space Complexity: O(1)
     */
    node_type getType() const;

    /**
     * @brief Returns the name of the reservoir, if the Vertex is a reservoir
     * @return const std::string&: name of the reservoir
     * @note Does not change attributes
     * @note Time Complexity: O(1), Space Complexity: O(1)
     */
    const std::string &getReservoir() const;

    /**
     * @brief Returns the municipality of the reservoir, if the Vertex is a reservoir
     * @return const std::string&: municipality of the reservoir
     * @note Does not change attributes
     * @note Time Complexity: O(1), Space Complexity: O(1)
     */
    const std::string &getMunicipality() const;

    /**
     * @brief Returns the name of the city, if the Vertex is a city
     * @return const std::string&: name of the city
     * @note Does not change attributes
     * @note Time Complexity: O(1), Space Complexity: O(1)
     */
    const std::string &getCity() const;

    /**
     * @brief Returns the number of people in the city, if the Vertex is a city
     * @return unsigned int: number of people in the city
     * @note Does not change attributes
     * @note Time Complexity: O(1), Space Complexity: O(1)
     */
    unsigned int getPopulation() const;

    /*
     * @brief Returns the demand of the city, if the Vertex is a city
     * @return double: demand of the city
     * @note Does not change attributes
     * @note Time Complexity: O(1), Space Complexity: O(1)
     */
    double getDemand() const;

    /**
     * @brief Returns the previous Vertex in the path, if existent
     * @return Vertex*: nullptr if not existent
     * @note Does not change attributes
     * @note Time Complexity: O(1), Space Complexity: O(1)
     */
    Vertex *getPrevious() const;
};

#endif // VERTEX_HPP

