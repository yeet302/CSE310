#ifndef STACK_H
#define STACK_H

#include <vector>

class Stack {
private:
    std::vector<int> stack;

public:
    void push(int v);
    int pop();
    bool isEmpty();
};

#endif 