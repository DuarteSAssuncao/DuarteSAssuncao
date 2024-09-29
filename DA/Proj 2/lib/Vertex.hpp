/**
* @file Vertex.hpp
* @brief Declaration of class Vertex
* @author G17_5
* @date 17/05/2024
*/

#ifndef VERTEX_HPP
#define VERTEX_HPP

// #define VERTEX_HAS_INCOMING

class Edge;

#include <vector>
#include <string>
#include <cfloat>
#include "Edge.hpp"

//! Cities, Reservoirs and Stations
class Vertex {
private:
    unsigned int id = 0;                        /*!< Each Vertex has an	unique ID */
    double latitude = 0;                        /*!< Latitude of the Vertex */
    double longitude = 0;                       /*!< Longitude of the Vertex */

    double dist = DBL_MAX;                      /*!< Distance from the source to this Vertex */
    bool visited = false;                       /*!< Whether this Vertex has already been visited in the current algorithm */
    bool leftBehind = false;                    /*!< Auxiliary field for some algorithms */
    Edge *path = nullptr;                       /*!< Previous edge on a path */

    std::vector<Edge *> adj;                     /*!< Outgoing edges */
#ifdef VERTEX_HAS_INCOMING
    std::vector<Edge*> incoming;                /*!< Incoming edges */
#endif /* VERTEX_HAS_INCOMING */
public:
    int queueIndex;
    /**
     * @brief Constructor
     * @param unsigned int id : unique identifier
     * @param double latitude : latitude of the Vertex
     * @param double longitude : longitude of the Vertex
     * @note Time Complexity : O(1), Space Complexity : O(1)
     */
    Vertex(unsigned int id, double latitude, double longitude);

    /**
     * @brief Returns the distance
     * @return double : distance
     * @note Does not change attributes
     * @note Time Complexity : O(1), Space Complexity : O(1)
     */
    double getDist() const;

    /**
     * @brief Returns whether the vertex was visited
     * @return bool : whether the vertex was visited
     * @note Does not change attributes
     * @note Time Complexity : O(1), Space Complexity : O(1)
     */
    bool isVisited() const;

    /**
     * @brief Returns the previous edge in the path
     * @return Edge* : previous edge in the path
     * @note Does not change attributes
     * @note Time Complexity : O(1), Space Complexity : O(1)
     */
    Edge *getPath() const;

    /**
     * @brief Returns the outgoing edges
     * @return std::vector<Edge*>& : vector of outgoing edges
     * @note Time Complexity : O(1), Space Complexity : O(1)
     */
    std::vector<Edge *> &getAdj();

#ifdef VERTEX_HAS_INCOMING
    /**
     * @brief Returns the incoming edges
     * @return std::vector<Edge*>& : vector of incoming edges
     * @note Time Complexity : O(1), Space Complexity : O(1)
     */
    std::vector<Edge*>& getIncoming();
#endif /* VERTEX_HAS_INCOMING */

    /**
     * @brief Sets the distance
     * @param double dist : updated distance
     * @return void
     * @note Time Complexity : O(1), Space Complexity : O(1)
     */
    void setDist(double dist);

    /**
     * @brief Sets whether the vertex was visited
     * @param bool visited : whether the vertex was visited
     * @return void
     * @note Time Complexity : O(1), Space Complexity : O(1)
     */
    void setVisited(bool visited);

    /**
     * @brief Sets the previous edge in the path
     * @param Edge* path : previous edge in the path
     * @return void
     * @note Time Complexity : O(1), Space Complexity : O(1)
     */
    void setPath(Edge *path);

    /**
     * @brief Adds an edge
     * @param Vertex* dest : destination
     * @param double l : length of the edge
     * @return Edge* : nullptr if not added
     * @note Time Complexity : O(1), Space Complexity : O(1)
     */
    Edge *addEdge(Vertex *dest, double l);

    /**
     * @brief Removes an edge
     * @param Vertex* v : destination
     * @return Edge* : nullptr if the edge does not exist
     * @note Time Complexity : O(E), Space Complexity : O(1)
     */
    bool removeEdge(Vertex *v);

    /**
     * @brief Returns the ID
     * @return unsigned int : ID of the Vertex
     * @note Does not change attributes
     * @note Time Complexity : O(1), Space Complexity : O(1)
     */
    unsigned int getId() const;

    /**
     * @brief Returns the latitude of the Vertex
     * @return double : latitude of the Vertex
     * @note Does not change attributes
     * @note Time Complexity : O(1), Space Complexity : O(1)
     */
    double getLatitude() const;

    /**
     * @brief Returns the longitude of the Vertex
     * @return double : longitude of the Vertex
     * @note Does not change attributes
     * @note Time Complexity : O(1), Space Complexity : O(1)
     */
    double getLongitude() const;

    /**
     * @brief Returns the previous Vertex in the path, if existent
     * @return Vertex* : nullptr if not existent
     * @note Does not change attributes
     * @note Time Complexity : O(1), Space Complexity : O(1)
     */
    Vertex *getPrevious() const;

    bool isLeftBehind() const;

    void setLeftBehind(bool leftBehind);

    /**
     * @return The distance (in meters) to the other vertex, calculated using the Haversine Distance
     * @note Time Complexity : O(1), Space Complexity : O(1)
     */
    double calcDistance(const Vertex *other) const;
};

#endif // VERTEX_HPP

