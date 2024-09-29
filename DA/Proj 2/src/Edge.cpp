/**
* @file Edge.cpp
* @brief Definition of class Edge
* @author G17_5
* @date 17/04/2024
*/

#include "../lib/Edge.hpp"

Edge::Edge(Vertex *orig, Vertex *dest, double l) : orig(orig), dest(dest), length(l) {}

Vertex *Edge::getOrig() const {
    return this->orig;
}

Vertex *Edge::getDest() const {
    return this->dest;
}

double Edge::getLength() const {
    return this->length;
}
