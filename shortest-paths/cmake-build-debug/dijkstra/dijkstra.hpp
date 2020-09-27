//
// Created by Andrei Zhikulin
//

#ifndef SHORTEST_PATHS_DIJKSTRA_HPP
#define SHORTEST_PATHS_DIJKSTRA_HPP

#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <fstream>
#include <mutex>
#include <sstream>
#include <map>
#include "edge.hpp"
#include "vertex.hpp"

using namespace std;

class dijkstra {
public:

    vector<vertex*> unvisited;
    vector<vertex> vertexes;
    vector<edge> edges;
    map<int, string> mapa;

    dijkstra();
    dijkstra(dijkstra &da);
    dijkstra(dijkstra *pDijkstra);

    static void startOneThreadMode(dijkstra* graph, int number);
    static void startMultiThreadMode(dijkstra* graph, int number);

    void computePath(int sourseId);
    string getShortestPathTo(int targedId);

    void createGraph(vector<vertex> vertexes, vector<edge> edgesToVertexes);
    void resetDijkstra();

    vertex findVertexById(int id) const;
    vertex findMinimum();

    void deleteVertex(int id);

    int getIndexById(vector<vertex> vector, int i);
    int getIndexById(vector<vertex*> vector, int i);

    void createGraphFromFile(string file_name);

};


#endif //SHORTEST_PATHS_DIJKSTRA_HPP
