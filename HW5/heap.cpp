#include "heap.h"
#include <algorithm>
#include <stdexcept> 

MinHeap::MinHeap(int cap) : cp(cap), size(0) {
    heap.resize(cp);
}

void MinHeap::insert(Vertex v) {

    if (size == cp) {
        throw std::overflow_error("Heap overflow");
    }

    size++;
    int i = size - 1;
    heap[i] = v;
    heapifyUp(i);
}

Vertex MinHeap::extractMin() {

    if (size <= 0) {
        throw std::underflow_error("Heap underflow");
    }

    if (size == 1) {
        size--;
        return heap[0];
    }

    Vertex root = heap[0];
    heap[0] = heap[size - 1];
    size--;
    heapifyDown(0);

    return root;
}

bool MinHeap::isEmpty() {
    return size == 0;
}

void MinHeap::heapifyUp(int i) {

    while (i != 0 && heap[parent(i)].key > heap[i].key) {
        std::swap(heap[i], heap[parent(i)]);
        i = parent(i);
    }
}

void MinHeap::heapifyDown(int i) {

    int l = left(i);
    int r = right(i);
    int smallest = i;

    if (l < size && heap[l].key < heap[smallest].key) {
        smallest = l;
    }
    if (r < size && heap[r].key < heap[smallest].key) {
        smallest = r;
    }
    if (smallest != i) {
        std::swap(heap[i], heap[smallest]);
        heapifyDown(smallest);
    }
}
