//
// Created by Andrei Zhikulin
//

#include <iostream>
#include <chrono>
#include <thread>
#include <cstring>
#include "dijkstra/dijkstra.hpp"

template<typename TimePoint>
std::chrono::milliseconds to_ms(TimePoint tp) { return std::chrono::duration_cast<std::chrono::milliseconds>(tp); }

// Single-thread scenario
void oneThread(string file) {
    try {
        dijkstra graph;
        graph.createGraphFromFile(file);

        auto start = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < graph.vertexes.size(); ++i) {
            if (i % 100 == 0) {
                graph.startOneThreadMode(&graph, i);
                auto curr = std::chrono::high_resolution_clock::now();
                cout << i << " vertexes are done " << "\tTime is " << to_ms(curr - start).count() << endl;
            } else if (i + 1 == graph.vertexes.size()) {
                auto curr1 = std::chrono::high_resolution_clock::now();
                cout << i + 1 << " vertexes are done " << "\tTime is " << to_ms(curr1 - start).count() << endl;
            } else
                graph.startOneThreadMode(&graph, i);
        }

        auto end = std::chrono::high_resolution_clock::now();

        cout << endl;

        // print output
        for (auto i = graph.mapa.begin(); i != graph.mapa.end(); i++) {
            cout << i->second << "\n";
        }

        std::cout << "Needed " << to_ms(end - start).count() << " ms to finish.\n";
    } catch (invalid_argument e) {
        throw e;
    }
}


/***
 * Method for creating a new threads and counting part of a graph
 * @param graph
 * @param from id of vertex
 * @param to id of vertex
 */
void workWithPart(dijkstra *graph, int from, int to) {
    vector<thread> th_vec;

    for (int i = from; i < to; ++i) {
        th_vec.emplace_back(dijkstra::startMultiThreadMode, graph, i);
    }

    for (auto &th : th_vec) {
        th.join();
    }

    th_vec.erase(th_vec.begin(), th_vec.end());
}


/**
 * Method for working in multi-threaded mode.
 * Creates a new thread for each vertex
 */
void multiThread(string file) {
    try {
        dijkstra graph;
        dijkstra *ref = &graph;

        graph.createGraphFromFile(file);

        vector<thread> th_vec;
        th_vec.reserve(graph.vertexes.size());

        int rest = graph.vertexes.size() % 100;

        auto start = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < graph.vertexes.size(); i += 100) {
            if (rest != 0 && i == graph.vertexes.size() - rest) {
                workWithPart(ref, i, i + rest);
                auto curr = std::chrono::high_resolution_clock::now();
                cout << i + rest << " vertexes are done " << "\tTime is " << to_ms(curr - start).count() << endl;
            } else {
                workWithPart(ref, i, i + 100);
                auto curr = std::chrono::high_resolution_clock::now();
                cout << i + 100 << " vertexes are done " << "\tTime is " << to_ms(curr - start).count() << endl;
            }
        }

        auto end = std::chrono::high_resolution_clock::now();

        cout << endl;

//      print output
        for (auto i = graph.mapa.begin(); i != graph.mapa.end(); i++) {
            cout << i->second << "\n";
        }

        std::cout << "Needed " << to_ms(end - start).count() << " ms to finish.\n";
    } catch (invalid_argument e) {
        throw e;
    }
}

int main(int argc, char **argv) {
    string argvFirst;
    string argvSecond;
    ifstream file;
    try {
        if (argc > 2) {
            if (strcmp(argv[1], "-one") == 0) {
                cout << "Hello my comrade!\n"
                     << "I would like to present you my program!\n"
                     << "You have selected a single-threaded program\n\n";
                argvSecond = argv[2];
                if (argv[2] != nullptr) {
                    file.open("data/" + argvSecond);
                    if (file.is_open()) {
                        oneThread(argvSecond);
                    } else {
                        std::cout << "Error opening file";
                    }
                } else {
                    cout << "You forgot to enter a file name :с\n";
                }
            } else if (strcmp(argv[1], "-multi") == 0) {
                cout << "Hello my comrade!\n"
                     << "I would like to present you mmy program!\n"
                     << "You have selected a multi-threaded program\n\n";
                argvSecond = argv[2];
                if (argv[2] != nullptr) {
                    file.open("data/" + argvSecond);
                    if (file.is_open()) {
                        multiThread(argvSecond);
                    } else {
                        std::cout << "Error opening file";
                    }
                } else {
                    cout << "You forgot to enter a file name :с\n";
                }
            } else if (strcmp(argv[1], "-help") == 0) {
                cout << "If you want one-thread program, use -one as argument.\n"
                     << "If you want multi-thread program, use -multi as argument.\n"
                     << "And name of file\n\n"
                     << "Example \"-one 1-dijkstra.txt\"\n";
            }
        } else if (argc > 1) {
            if (strcmp(argv[1], "-help") == 0) {
                cout << "If you want one-thread mode, use -one as argument.\n"
                     << "If you want multi-thread mode, use -multi as argument.\n\n"
                     << "And name of file\n\n"
                     << "Example \"-one 1-dijkstra.txt\"\n";
            } else {
                cout << "Wrong argument :c \n"
                     << "Please, use -help for more information.\n";
                return 1;
            }
        } else {
            cout << "Wrong argument :c \n"
                 << "Please, use -help for more information.\n";
            return 1;
        }
    } catch (invalid_argument e) {
        throw e;
    }
    return 0;
}
