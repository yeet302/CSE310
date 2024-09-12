#include "stack.h"
#include <stdexcept> 

void Stack::push(int v) {
    stack.push_back(v);
}

int Stack::pop() {
    if (stack.empty()) {
        throw std::underflow_error("Stack underflow");
    }

    int top = stack.back();
    stack.pop_back();
    return top;
}

bool Stack::isEmpty() {
    return stack.empty();
}

/**/