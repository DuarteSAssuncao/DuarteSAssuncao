/**
* @file Edge.cpp
* @brief Definition of class Edge
* @author G17_5
* @date 09/03/2024
*/

#include "../lib/Edge.hpp"

Edge::Edge(Vertex *orig, Vertex *dest, double w) : orig(orig), dest(dest), weight(w) {}

double Edge::getFlow() const {
    return flow;
}

double Edge::getWeight() const {
    return this->weight;
}

Vertex *Edge::getOrig() const {
    return this->orig;
}

Vertex *Edge::getDest() const {
    return this->dest;
}

void Edge::setFlow(double flow) {
    this->flow = flow;
}
