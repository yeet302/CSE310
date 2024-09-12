#include "graph.h"
#include "heap.h"
#include "stack.h"
#include <iostream>
#include <queue>
#include <limits>
#include <iomanip> 

using namespace std;

#define FLT_MAX numeric_limits<float>::max()

Graph::Graph(int vertices, int edges) : n(vertices), m(edges), adjList(vertices + 1) {}

void Graph::addEdge(int u, int v, float w, bool atRear) {
    Edge edge = { u, v, w };
    if (atRear) {
        adjList[u].push_back(edge);  
    }
    else {
        adjList[u].insert(adjList[u].begin(), edge);  
    }
}

void Graph::dijkstra(int source) {
    for (int i = 1; i <= n; ++i) {
        vertices[i] = { i, FLT_MAX, -1 };
    }
    vertices[source].key = 0;

    MinHeap minHeap(n);
    minHeap.insert(vertices[source]);

    while (!minHeap.isEmpty()) {
        Vertex u = minHeap.extractMin();

        for (const Edge& edge : adjList[u.index]) {
            if (vertices[edge.v].key > vertices[u.index].key + edge.w) {
                vertices[edge.v].key = vertices[u.index].key + edge.w;
                vertices[edge.v].pi = u.index;
                minHeap.insert(vertices[edge.v]);
            }
        }
    }
}

void Graph::printAdj() {
    for (int i = 1; i <= n; ++i) {
        cout << "ADJ[" << i << "]: ";
        for (const Edge& edge : adjList[i]) {
            cout << "-->" << "[" << edge.u << " " << edge.v << ": " << fixed << setprecision(2) << edge.w << "] ";
        }
        cout << endl;
    }
}



void Graph::printPath(int s, int t) {
    if (vertices[t].pi == -1) {

        cout << "There is no path from " << s << " to " << t << "." << endl;
        return;
    }

    Stack path;
    for (int v = t; v != -1; v = vertices[v].pi) {
        path.push(v);
    }

    cout << "The shortest path from " << s << " to " << t << " is: ";
    while (!path.isEmpty()) {
        int v = path.pop();
        if (path.isEmpty()) {

            cout << "[" << v << ": " << fixed << setprecision(2) << vertices[v].key << "]." << endl;
        }
        else 
        {
            cout << "[" << v << ": " << fixed << setprecision(2) << vertices[v].key << "]-->";
        }
    }
}

void Graph::printLength(int s, int t) {
    if (vertices[t].pi == -1) {
        cout << "There is no path from " << s << " to " << t << "." << endl;
    }
    else {
        cout << "The length of the shortest path from " << s << " to " << t << " is: " << fixed << setprecision(2) << vertices[t].key << endl;
    }
}
