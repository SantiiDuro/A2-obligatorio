#ifndef BFS_IMP
#define BFS_IMP

#include <cstddef>
#include "../tads/Graph.h"
#include "../tads/Queue.h"
#include "../tads/QueueImp.cpp"

bool bfsBipartite(Graph* graph, int source, int* color)
{
    Queue<int>* queue = new QueueImp<int>();
    color[source] = 0;
    queue->enqueue(source);

    while (!queue->isEmpty())
    {
        int vertex = queue->dequeue();
        int currentColor = color[vertex];
        NodeList<Edge>* adjacents = graph->getAdjacents(vertex);
        
        while (adjacents != NULL)
        {
            int adjacentVertex = adjacents->element.to;
            int colorAdjacent = color[adjacentVertex];

            if (colorAdjacent == -1)
            {
                color[adjacentVertex] = 1 - currentColor;
                queue->enqueue(adjacentVertex);
            }
            else if (colorAdjacent == currentColor)
            {
                delete queue;
                return false;
            }

            adjacents = adjacents->next;
        }
    }

    delete queue;
    return true;
}

#endif
