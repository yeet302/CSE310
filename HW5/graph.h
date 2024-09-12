#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <unordered_map>

struct Edge {
    int u, v;
    float w;
};

struct Vertex {
    int index;
    float key;
    int pi;
};

class Graph {
private:
    int n, m;
    std::vector<std::vector<Edge>> adjList;
    std::unordered_map<int, Vertex> vertices;

public:
    Graph(int vertices, int edges);
    void addEdge(int u, int v, float w, bool atRear = false);
    void dijkstra(int source);
    void printAdj();
    void printPath(int s, int t);
    void printLength(int s, int t);
};

#endif 
