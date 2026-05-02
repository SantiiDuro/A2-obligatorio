#ifndef NODE_HEAP
#define NODE_HEAP

struct NodeHeap
{
    int element;
    int cost;

    NodeHeap() {}
    NodeHeap(int el, int c) : element(el), cost(c) {}
};

#endif