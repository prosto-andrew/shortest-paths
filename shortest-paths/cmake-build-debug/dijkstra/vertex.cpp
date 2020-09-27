//
// Created by Andrei Zhikulin
//

#include "vertex.hpp"

/**
 * Konstruktory tridy Vertex
 */
vertex::vertex(int id, string name) {
    this->id = id;
    this->name = name;
    this->minDistance = numeric_limits<float>::infinity();
}

vertex::vertex(int id, string name, float minDistance, vertex *prevVertex, vector<edge> edges) {
    this->id = id;
    this->name = name;
    this->minDistance = minDistance;
    this->prevVertex = prevVertex;
    this->edges = edges;
}

vertex::vertex(const vertex &nv) {
    this->id = nv.id;
    this->name = nv.name;
    this->minDistance = nv.minDistance;
    this->prevVertex = nv.prevVertex;
    this->edges = nv.edges;
}

vertex::vertex(vertex &&nv) {
    this->id = nv.id;
    this->name = nv.name;
    this->minDistance = nv.minDistance;
    this->prevVertex = nv.prevVertex;
    this->edges = nv.edges;
}

vertex &vertex::operator=(const vertex &nv) {
    this->id = nv.id;
    this->name = nv.name;
    this->minDistance = nv.minDistance;
    this->prevVertex = nv.prevVertex;
    this->edges = nv.edges;
    return *this;
}