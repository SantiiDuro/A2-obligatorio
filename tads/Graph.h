#ifndef GRAPH_H
#define GRAPH_H

#include "NodeList.cpp"
#include "Edge.cpp"

class Graph
{
public:
    virtual ~Graph() {}
    virtual void addEdge(int src, int dest, int weight = 1) = 0;
    virtual NodeList<Edge>* getAdjacents(int vertex) = 0;
    virtual int getV() = 0;
    virtual int getA() = 0;
};

#endif