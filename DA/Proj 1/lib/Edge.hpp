/**
 * @file Edge.hpp
 * @brief Declaration of class Edge
 * @author G17_5
 * @date 09/03/2024
 */

#ifndef EDGE_HPP
#define EDGE_HPP

class Vertex;

#include "Vertex.hpp"

//! Pipes
class Edge {
private:
    Vertex *orig = nullptr;                       /*!< Origin of the edge */
    Vertex *dest = nullptr;                       /*!< Destination of the edge */
    double weight = 0;                            /*!< Weight of the edge (can also be taken as capacity) */
    double flow = 0;                              /*!< Current flow passing through the edge*/

public:
    /** 
     * @brief Constructor taking an origin, a destination and a Weight
     * @param Vertex* orig: origin
     * @param Vertex* dest: destination
     * @param double w: capacity of the edge
     * @note Time Complexity: O(1), Space Complexity: O(1)
     */ 
    Edge(Vertex *orig, Vertex *dest, double w);   

    /** 
     * @brief Returns the flow of the edge
     * @return double: the flow of the edge
     * @note Does not change attributes
     * @note Time Complexity: O(1), Space Complexity: O(1)
     */
    double getFlow() const;

    /**
     * @brief Return the capacity of the edge
     * @return double: the capacity of the edge
     * @note Does not change attributes
     * @note Time Complexity: O(1), Space Complexity: O(1)
     */
    double getWeight() const;

    /** 
     * @brief Return the origin of the edge
     * @return Vertex*: the destination
     * @note Does not change attributes
     * @note Time Complexity: O(1), Space Complexity: O(1)
     */
    Vertex *getOrig() const;

    /** 
     * @brief Return the destination of the edge
     * @return Vertex*: the destination
     * @note Does not change attributes
     * @note Time Complexity: O(1), Space Complexity: O(1)
     */
    Vertex *getDest() const;

    /** 
     * @brief Changes the value of the flow
     * @param double flow: the updated flow of the edge
     * @return void
     * @note Time Complexity: O(1), Space Complexity: O(1)
     */
    void setFlow(double flow);
};

#endif // EDGE_HPP

