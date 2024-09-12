#ifndef HEAP_H
#define HEAP_H

#include "graph.h"
#include <vector>

class MinHeap {
private:
    std::vector<Vertex> heap;
    int cp;
    int size;
    int parent(int i) { return (i - 1) / 2; }
    int left(int i) { return (2 * i + 1); }
    int right(int i) { return (2 * i + 2); }
    void heapifyUp(int i);
    void heapifyDown(int i);

public:
    MinHeap(int capacity);
    void insert(Vertex v);
    Vertex extractMin();
    bool isEmpty();
};

#endif 
