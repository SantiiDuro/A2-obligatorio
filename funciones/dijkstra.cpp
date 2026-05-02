// funciones/dijkstra.cpp
#ifndef DIJKSTRA_IMP
#define DIJKSTRA_IMP

#include <climits>
#include <cstddef>
#include "../tads/Graph.h"
#include "../tads/BinaryHeap.h"
#include "../tads/BinaryHeapImp.cpp"
#include "../tads/NodeHeap.cpp"

#define INF INT_MAX

bool isLessThan(NodeHeap a, NodeHeap b)
{
    return a.cost < b.cost;
}

int* dijkstra(Graph* graph, int source)
{
    int V = graph->getV();
    int A = graph->getA();
    bool* visited = new bool[V+1]();
    int* cost = new int[V+1]();
    int* parent = new int[V+1]();

    HeapImp<NodeHeap>* minHeap = new HeapImp<NodeHeap>(V+A, isLessThan);

    for (int i = 1; i <= V; i++)
    {
        cost[i] = INF;
        parent[i] = -1;
    }

    cost[source] = 0;
    NodeHeap sourceNode(source, 0);
    minHeap->insert(sourceNode);

    while (!minHeap->isEmpty())
    {
        NodeHeap currentNode = minHeap->top();
        int currentVertex = currentNode.element;
        minHeap->removeTop();

        if (!visited[currentVertex])
        {
            visited[currentVertex] = true;
            NodeList<Edge>* adjacents = graph->getAdjacents(currentVertex);

            while (adjacents != NULL)
            {
                int w = adjacents->element.to;
                int edgeCost = adjacents->element.weight;

                if (cost[w] > cost[currentVertex] + edgeCost)
                {
                    cost[w] = cost[currentVertex] + edgeCost;
                    parent[w] = currentVertex;
                    NodeHeap newNode(w, cost[w]);
                    minHeap->insert(newNode);
                }

                adjacents = adjacents->next;
            }
        }
    }
    
    delete[] visited;
    delete[] parent;
    delete minHeap;

    return cost;
}

#endif