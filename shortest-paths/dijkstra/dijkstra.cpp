//
// Created by Andrei Zhikulin
//

#include "dijkstra.hpp"
#include <iostream>
#include <string>
#include <mutex>

mutex mu;

// Constructors for dijkstra
dijkstra::dijkstra() {}

dijkstra::dijkstra(dijkstra &di) {
    this->vertexes = di.vertexes;
    this->unvisited = di.unvisited;
    this->edges = di.edges;
    this->mapa = di.mapa;
}

dijkstra::dijkstra(dijkstra *pDijkstra) {
    this->vertexes = pDijkstra->vertexes;
    this->unvisited = pDijkstra->unvisited;
    this->edges = pDijkstra->edges;
    this->mapa = pDijkstra->mapa;
}


/**
 * Method for creating output for a graph.
 * @param graph
 * @param number is id of vertex
 */
void dijkstra::startOneThreadMode(dijkstra *graph, int number) {
    dijkstra new_graph;
    new_graph = graph;

    new_graph.computePath(number);

    string str = "#  S_T_A_R_T  G_R_A_P_H  " + to_string(number) + "\n\n";

    for (int i = 0; i < graph->vertexes.size(); ++i) {
        str += new_graph.getShortestPathTo(i);
    }

    graph->mapa.insert(pair<int, string>(number, str));
}

/**
 * Method for creating output for a graph in multi threading mode.
 * Фparam graph
 * @param number is id of vertex
 */

void dijkstra::startMultiThreadMode(dijkstra *graph, int number) {
    dijkstra new_graph;
    new_graph = graph;

    new_graph.computePath(number);

    string str = "#  S_T_A_R_T  G_R_A_P_H  " + to_string(number) + "\n\n";

    for (int i = 0; i < graph->vertexes.size(); ++i) {
        str += new_graph.getShortestPathTo(i);
    }

    mu.lock();
    graph->mapa.insert(pair<int, string>(number, str));
    mu.unlock();
}

/**
 * Calculates the shortest path between a vertex with the id transmitted as a parameter to the function, and all other
 * @param sourceId the id of the vertex from which it calculates the shortest path to all the top of the chart
 */
void dijkstra::computePath(int sourseId) {
    int index = this->getIndexById(this->vertexes, sourseId);
    vertex *currentVertex = &this->vertexes[index];
    for (int i = 0; i < this->vertexes.size(); ++i) {
        if (vertexes[i].id != sourseId) {
            vertex *unVer = &this->vertexes[i];
            unvisited.push_back(unVer);
        }
    }
    currentVertex->minDistance = 0;
    while (!unvisited.empty()) {
        for (edge edge : currentVertex->edges) {
            int targetIndex = this->getIndexById(this->vertexes, edge.target);
            vertex *targetVertex = &vertexes[targetIndex];
            if ((edge.weight + currentVertex->minDistance) < targetVertex->minDistance) {
                targetVertex->prevVertex = currentVertex;
                targetVertex->minDistance = edge.weight + currentVertex->minDistance;
            }
        }
        deleteVertex(currentVertex->id);
        if (!unvisited.empty())
            currentVertex = unvisited[this->getIndexById(this->unvisited, findMinimum().id)];
    }
}

/**
 * The method creates string with short paths from all vertexes to the target vertex
 * @param targetId the id of the top
 */
string dijkstra::getShortestPathTo(int targedId) {
    vector<vertex> wayOfVertexes;
    wayOfVertexes.reserve(5000);
    vertex currentVertex = findVertexById(targedId);
    while (true) {
        if (currentVertex.prevVertex == nullptr) {
            wayOfVertexes.push_back(currentVertex);
            break;
        }
        wayOfVertexes.push_back(currentVertex);
        currentVertex = *currentVertex.prevVertex;
    }
    reverse(wayOfVertexes.begin(), wayOfVertexes.end());
    int minDist = 0;
    for (auto &way : wayOfVertexes) {
        if (way.prevVertex != nullptr) {
            for (int j = 0; j < way.edges.size(); ++j) {
                if (way.edges[j].target == way.prevVertex->id)
                    minDist += way.edges[j].weight;
            }
        }
    }
    reverse(wayOfVertexes.begin(), wayOfVertexes.end());

    // create string with result
    string result;
    if (minDist != 0) {
        result += "Minimum path from " + wayOfVertexes[0].name + " to " + wayOfVertexes[wayOfVertexes.size() - 1].name +
                  "\n";
        ostringstream oss;
        for (int i = 0; i < wayOfVertexes.size(); ++i) {
            oss << " " << wayOfVertexes[i].name << " ";
        }
        result += "Way is " + oss.str() + "\n";
        result += "Distance is " + to_string(minDist) + "\n";
        result += "=============================================\n";
    }
    return result;
}

/**
 * The function takes two vectors and creates a graph
 * @param vertexes
 * @param edgesToVertexes
 */
void dijkstra::createGraph(vector<vertex> vertexes, vector<edge> edgesToVertexes) {
    this->vertexes = vertexes;
    for (edge edge : edgesToVertexes) {
        for (int i = 0; i < this->vertexes.size(); ++i) {
            if (edge.source == this->vertexes[i].id)
                this->vertexes[i].edges.push_back(edge);
        }
    }
}

void dijkstra::resetDijkstra() {
    for (int i = 0; i < this->vertexes.size(); ++i) {
        this->vertexes[i].id = 0;
        this->vertexes[i].name = "";
        this->vertexes[i].minDistance = 0;
        this->vertexes[i].prevVertex = nullptr;
//        this->vertexes[i].edges = {};
    }
}

// Function to find the vertex by id
vertex dijkstra::findVertexById(int id) const {
    for (vertex vert : vertexes) {
        if (vert.id == id)
            return vert;
    }
}

// Function to find the vertex with the miniDistance
vertex dijkstra::findMinimum() {
    vertex *minVertex;
    for (int i = 0; i < this->unvisited.size(); ++i) {
        if (i == 0) {
            minVertex = unvisited[0];
        } else if (unvisited[i]->minDistance <= minVertex->minDistance)
            minVertex = unvisited[i];
    }
    return *minVertex;
}

// Function for deleting vertex
void dijkstra::deleteVertex(int id) {
    for (int i = 0; i < this->unvisited.size(); ++i) {
        if (unvisited[i]->id == id) {
            unvisited.erase(unvisited.begin() + i);
        }
    }
}

int inline dijkstra::getIndexById(vector<vertex> vertexes, int id) {
    for (int i = 0; i < vertexes.size(); ++i) {
        if (vertexes[i].id == id)
            return i;
    }
}

int inline dijkstra::getIndexById(vector<vertex *> vertexes, int id) {
    for (int i = 0; i < vertexes.size(); ++i) {
        if (vertexes[i]->id == id)
            return i;
    }
}

// Function for parsing data from a file
void dijkstra::createGraphFromFile(string file_name) {
    ifstream file;
    file.open("data/" + file_name);
    vector<vertex> vertexes;
    vector<edge> edges;
    bool isVertex = false;
    bool isEdge = false;
    while (!file.eof()) {
        string str;
        file >> str;
        if (str == "vertexes") {
            isVertex = true;
            isEdge = false;
        } else if (str == "edges") {
            isEdge = true;
            isVertex = false;
        } else if (isVertex) {
            int id = atoi(str.c_str());
            string name;
            file >> name;
            vertex vert = {id, name};
            vertexes.push_back(vert);
            if (vert.id == 5000)
                cout << vert.id << endl;
        } else if (isEdge) {
            int source = atoi(str.c_str());
            int target;
            file >> target;
            int weight;
            file >> weight;
            edge edge = {source, target, weight};
            edges.push_back(edge);
            if (edge.source == 5000)
                cout << edge.source << endl;
        }
    }
    createGraph(vertexes, edges);
}