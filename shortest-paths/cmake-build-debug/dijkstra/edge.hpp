//
// Created by Andrei Zhikulin
//

#ifndef SHORTEST_PATHS_EDGE_HPP
#define SHORTEST_PATHS_EDGE_HPP

// Struct to represent an edge
struct edge {
    int source = 0;
    int target = 0;
    int weight = 0;

    edge(int source, int target, int weight);
};


#endif //SHORTEST_PATHS_EDGE_HPP
