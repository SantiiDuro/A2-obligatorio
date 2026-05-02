#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "tads/Graph.h"
#include "tads/AdjacencyList.cpp"
#include "funciones/bfs.cpp"

using namespace std;

bool isBipartite(Graph* graph)
{
    int V = graph->getV();
    int* color = new int[V+1];

    for (int i = 1; i <= V; i++)
        color[i] = -1;

    for (int i = 1; i <= V; i++)
    {
        if (color[i] == -1)
        {
            if (!bfsBipartite(graph, i, color))
            {
                delete[] color;
                return false;
            }
        }
    }
    delete[] color;
    return true;
}

int main()
{
    int cantVertex, cantEdges = 0;

    cin >> cantVertex >> cantEdges;

    Graph* graph = new AdjacencyList(cantVertex, false, false);

    for (int i = 0; i < cantEdges; i++)
    {
        int student1, student2;
        cin >> student1 >> student2;
        graph->addEdge(student1, student2);
    }

    bool solution = isBipartite(graph);
    
    if (solution)
        cout << "SI" << endl;
    else
        cout << "NO" << endl;

    return 0;
}