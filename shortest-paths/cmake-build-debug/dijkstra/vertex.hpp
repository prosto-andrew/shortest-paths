//
// Created by Andrei Zhikulin
//

#ifndef SHORTEST_PATHS_VERTEX_HPP
#define SHORTEST_PATHS_VERTEX_HPP

#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <fstream>
#include "edge.hpp"

using namespace std;
// Struct to represent an vertex
struct vertex {
    int id = 0;
    string name = "";
    float minDistance = numeric_limits<float>::infinity();
    vertex* prevVertex = nullptr;
    vector<edge> edges;

    vertex(){}
    vertex(int id, string name);
    vertex(int id, string name, float minDistance, vertex* prevVertex, vector<edge> edges);
    vertex(const vertex& nv);
    vertex(vertex && nv);
    vertex& operator=(const vertex& nv);
//    vertex operator*(vertex v , vertex const& nv){
//        return nv * v;
//    }
};

#endif //SHORTEST_PATHS_VERTEX_HPP
