#ifndef EDGE_IMP
#define EDGE_IMP

struct Edge
{
    int from;
    int to;
    int weight;

    Edge(int f, int t, int w) : from(f), to(t), weight(w) {}
    Edge(int f, int t) : from(f), to(t), weight(1) {}
    Edge() {}
    ~Edge() {}
};

#endif