/**
* @file Vertex.cpp
* @brief Definition of class Vertex
* @author G17_5
* @date 09/03/2024
*/

#include "../lib/Vertex.hpp"
#include <iostream>
#include <utility>

//! Time Complexity: O(1), Space Complexity: O(1)
Vertex::Vertex(unsigned int id, double latitude, double longitude) : id(id), latitude(latitude), longitude(longitude) {}

//! Time Complexity: O(1), Space Complexity: O(1)
double Vertex::getDist() const {
    return this->dist;
}

//! Time Complexity: O(1), Space Complexity: O(1)
bool Vertex::isVisited() const {
    return this->visited;
}

//! Time Complexity: O(1), Space Complexity: O(1)
Edge *Vertex::getPath() const {
    return this->path;
}

//! Time Complexity: O(1), Space Complexity: O(1)
std::vector<Edge *> &Vertex::getAdj() {
    return this->adj;
}

#ifdef VERTEX_HAS_INCOMING
//! Time Complexity: O(1), Space Complexity: O(1)
std::vector<Edge*>& Vertex::getIncoming() {
  return this->incoming;
}
#endif /* VERTEX_HAS_INCOMING */

//! Time Complexity: O(1), Space Complexity: O(1)
void Vertex::setDist(double dist) {
    this->dist = dist;
}

//! Time Complexity: O(1), Space Complexity: O(1)
void Vertex::setVisited(bool visited) {
    this->visited = visited;
}

//! Time Complexity: O(1), Space Complexity: O(1)
void Vertex::setPath(Edge *path) {
    this->path = path;
}

//! Time Complexity: O(1), Space Complexity: O(1)
Edge *Vertex::addEdge(Vertex *dest, double w) {
    Edge *newEdge = new Edge(this, dest, w);
    adj.push_back(newEdge);
#ifdef VERTEX_HAS_INCOMING
    dest->incoming.push_back(newEdge);
#endif /* VERTEX_HAS_INCOMING */
    return newEdge;
}

//! Time Complexity: O(n), Space Complexity: O(1) with n being the sum of the number of outgoing and incoming edges
bool Vertex::removeEdge(Vertex *v) {
    for (std::vector<Edge *>::iterator itr = this->adj.begin(); itr != this->adj.end(); itr++) {
        if ((*itr)->getDest() == v) {
            Edge *to_remove = *itr;
#ifdef VERTEX_HAS_INCOMING
            for (std::vector<Edge *>::iterator sitr = v->incoming.begin(); sitr != v->incoming.end(); sitr++) {
              if (*sitr == to_remove) {
                sitr = v->incoming.erase(sitr);
                break;
              }
            }
#endif /* VERTEX_HAS_INCOMING */
            itr = this->adj.erase(itr);
            delete to_remove;
            return true;
        }
    }
    std::cerr << "Vertex not found\n";
    return false;
}

//! Time Complexity: O(1), Space Complexity: O(1)
unsigned int Vertex::getId() const {
    return this->id;
}

double Vertex::getLatitude() const {
    return this->latitude;
}

double Vertex::getLongitude() const {
    return this->longitude;
}

//! Time Complexity: O(1), Space Complexity: O(1)
Vertex *Vertex::getPrevious() const {
    return (path->getDest() == this) ? path->getOrig() : path->getDest();
}

bool Vertex::isLeftBehind() const {
    return leftBehind;
}

void Vertex::setLeftBehind(bool leftBehind) {
    Vertex::leftBehind = leftBehind;
}

#include <cmath>
#ifndef M_PI
    #define M_PI 3.14159265358979323846264338327950288
#endif

double Vertex::calcDistance(const Vertex *other) const {
    double rlat1 = this->getLatitude() * M_PI / 180;
    double rlat2 = other->getLatitude() * M_PI / 180;
    double rlon1 = this->getLongitude() * M_PI / 180;
    double rlon2 = other->getLongitude() * M_PI / 180;
    double delta_lat = rlat2 - rlat1;
    double delta_lon = rlon2 - rlon1;

    double aux = pow(sin(delta_lat/2),2) + cos(rlat1) * cos(rlat2) * pow((delta_lon/2),2);
    return 6371000 * 2 * atan2(sqrt(aux), sqrt(1 - aux));
}
