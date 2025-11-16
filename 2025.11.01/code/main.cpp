#include <iostream>

struct SStack {
    int* arr;
    size_t size;
};


void push(struct SStack* stack, int value) ;
void pop(struct SStack* stack) ;
int top(struct SStack* stack);
int empty(struct SStack* stack);

SStack createStack() {
    return {};
}

int main(int, char**){
    SStack stack = createStack();
    stack.size = 100500; // OOps
    stack.arr = NULL; // OOps
}
