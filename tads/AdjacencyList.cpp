#ifndef ADJACENCY_LIST_IMP
#define ADJACENCY_LIST_IMP

#include <cstddef>
#include <cassert>
#include "NodeList.cpp"
#include "Graph.h"

class AdjacencyList : public Graph
{
public:
    AdjacencyList(int v, bool _isWeighted, bool _isDirected)
    {
        V = v;
        A = 0;
        isWeighted = _isWeighted;
        isDirected = _isDirected;
        nodeList = new NodeList<Edge>*[V+1]();
        for (int i = 1; i <= V; i++)
            nodeList[i] = NULL;
    }

    void addEdge(int src, int dest, int weight = 1)
    {
        assert(isWeighted || weight == 1);
        Edge edge(src, dest, weight);
        nodeList[src] = new NodeList<Edge>(edge, nodeList[src]);
        if (!isDirected)
        {
            Edge reverseEdge(dest, src, weight);
            nodeList[dest] = new NodeList<Edge>(reverseEdge, nodeList[dest]);
        }

        A++;
    }

    NodeList<Edge>* getAdjacents(int src)
    {
        NodeList<Edge>* ret = NULL;
        NodeList<Edge>* aux = nodeList[src];
        while (aux != NULL)
        {
            ret = new NodeList<Edge>(aux->element, ret);
            aux = aux->next;
        }
        
        return ret;
    }

    int getV() { return V; }
    
    int getA() { return A; }

private:
    NodeList<Edge>** nodeList;
    int V;
    int A;
    bool isWeighted;
    bool isDirected;
};

#endif
