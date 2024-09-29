/**
* @file Vertex.cpp
* @brief Definition of class Vertex
* @author G17_5
* @date 09/03/2024
*/

#include "../lib/Vertex.hpp"
#include "../lib/GraphException.hpp"
#include <iostream>
#include <utility>

//! Time Complexity: O(1), Space Complexity: O(1)
Vertex::Vertex(
        node_type type,
        unsigned int id,
        const std::string reservoir,
        const std::string municipality,
        const std::string city,
        unsigned int population) :
        type(type), id(id), reservoir(reservoir), municipality(municipality), city(city), population(population) {}

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

//! Time Complexity: O(1), Space Complexity: O(1)
std::vector<Edge *> &Vertex::getIncoming() {
    return this->incoming;
}

//! Time Complexity: O(1), Space Complexity: O(1)
const std::vector<Edge *> &Vertex::getAdj() const noexcept {
    return this->adj;
}

//! Time Complexity: O(1), Space Complexity: O(1)
const std::vector<Edge *> &Vertex::getIncoming() const noexcept {
    return this->incoming;
}

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
    dest->incoming.push_back(newEdge);
    return newEdge;
}

//! Time Complexity: O(n), Space Complexity: O(1)
//! with n being the sum of the number of outgoing edges of "this" and the incoming edges of "v"
Edge *Vertex::removeEdge(Vertex *v) {
    for (std::vector<Edge *>::iterator itr = this->adj.begin(); itr != this->adj.end(); itr++) {
        if ((*itr)->getDest() == v) {
            Edge *to_remove = *itr;
            for (std::vector<Edge *>::iterator sitr = v->incoming.begin(); sitr != v->incoming.end(); sitr++) {
                if (*sitr == to_remove) {
                    sitr = v->incoming.erase(sitr);
                    break;
                }
            }
            itr = this->adj.erase(itr);
            return to_remove;
        }
    }
    std::cerr << "Vertex not found\n";
    return nullptr;
}

//! Time Complexity: O(1), Space Complexity: O(1)
unsigned int Vertex::getId() const {
    return this->id;
}

//! Time Complexity: O(1), Space Complexity: O(1)
unsigned int Vertex::getTypeId() const {
    return this->id / 10;
}

std::string Vertex::getCode() const {
    switch (this->type) {
        case STATION:   return "PS_" + std::to_string(getTypeId());
        case CITY:      return "C_" + std::to_string(getTypeId());
        case RESERVOIR: return "R_" + std::to_string(getTypeId());
        case SOURCE:    return "SRC";
        case SINK:      return "SNK";
        default:        return "IDK";
    }
}

//! Time Complexity: O(1), Space Complexity: O(1)
node_type Vertex::getType() const {
    return this->type;
}

//! Time Complexity: O(1), Space Complexity: O(1)
const std::string &Vertex::getReservoir() const {
    if (type != RESERVOIR)
        throw GraphException("Tried to get the reservoir name of a node that is not a reservoir");
    return this->reservoir;
}

//! Time Complexity: O(1), Space Complexity: O(1)
const std::string &Vertex::getMunicipality() const {
    if (type != RESERVOIR)
        throw GraphException("Tried to get the municipality of a node that is not a municipality");
    return this->municipality;
}

//! Time Complexity: O(1), Space Complexity: O(1)
const std::string &Vertex::getCity() const {
    if (this->type != CITY)
        throw GraphException("Tried to get the city name of a node that is not a city");
    return this->city;
}

//! Time Complexity: O(1), Space Complexity: O(1)
unsigned int Vertex::getPopulation() const {
    if (this->type != CITY)
        throw GraphException("Tried to get the population of a node that is not a city");
    return this->population;
}

//! Time Complexity: O(1), Space Complexity: O(1)
double Vertex::getDemand() const {
    if (this->type != CITY)
        throw GraphException("Tried to get the demand of a node that is not a city");
    return this->adj[0]->getWeight();
}

//! Time Complexity: O(1), Space Complexity: O(1)
Vertex *Vertex::getPrevious() const {
    return (path->getDest() == this) ? path->getOrig() : path->getDest();
}

const std::vector<std::pair<Edge *, double>> &Vertex::getDependency() const {
    if (this->type != CITY)
        throw GraphException("Tried to get the dependency vector of a node that is not a city");
    return this->dependency;
}

void Vertex::addDependency(Edge *e, double value) {
    if (this->type != CITY)
        throw GraphException("Tried to add to the dependency vector of a node that is not a city");
    this->dependency.emplace_back(e, value);
}
