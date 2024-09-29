/**
 * @file Edge.hpp
 * @brief Declaration of class Edge
 * @author G17_5
 * @date 17/05/2024
 */

#ifndef EDGE_HPP
#define EDGE_HPP

class Vertex;

#include "Vertex.hpp"
#include "Macros.hpp"

//! Streets between cities
class Edge {
  private:
    Vertex* orig = nullptr;                       /*!< Origin of the edge */
    Vertex* dest = nullptr;                       /*!< Destination of the edge */
    double length = 0;                            /*!< Distance between two cities */

  public:
    /** 
    * @brief Constructor taking an origin, a destination and a Weight
    * @param Vertex* orig : origin
    * @param Vertex* dest : destination
    * @param double l : length of the edge
    * @note Time Complexity : O(1), Space Complexity : O(1)
    */ 
    Edge(Vertex* orig, Vertex* dest, double l);

    /**
    * @brief Return the length of the edge
    * @return double : the length of the edge
    * @note Does not change attributes
    * @note Time Complexity : O(1), Space Complexity : O(1)
    */
    double getLength() const;

    /** 
    * @brief Return the origin of the edge
    * @return Vertex* : the destination
    * @note Does not change attributes
    * @note Time Complexity : O(1), Space Complexity : O(1)
    */
    Vertex* getOrig() const;

    /** 
    * @brief Return the destination of the edge
    * @return Vertex* : the destination
    * @note Does not change attributes
    * @note Time Complexity : O(1), Space Complexity : O(1)
    */
    Vertex* getDest() const;
};

#endif // EDGE_HPP

