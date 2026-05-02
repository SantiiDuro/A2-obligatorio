#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "tads/Hash.h"
#include "tads/OpenHashImp.cpp"
#include "tads/Graph.h"
#include "tads/AdjacencyList.cpp"
#include "funciones/dijkstra.cpp"

using namespace std;

int hash3(string key)
{
    int h = 0;
    for (int i = 0; i < key.length(); i++)
        h = 31 * h + int(key[i]);
    return h;
}

int minEnergyBetweenPlanets(Graph* graph, OpenHashImp<string, int>* hash, string startPlanet, string endPlanet)
{
    if (!hash->contains(startPlanet) || !hash->contains(endPlanet))
        return -1;

    int startIndex = hash->get(startPlanet);
    int endIndex = hash->get(endPlanet);

    int* costs = dijkstra(graph, startIndex);
    int minEnergy = costs[endIndex];

    delete[] costs;

    return minEnergy == INF ? -1 : minEnergy;
}

int main()
{
    int planetsCount, portalsCount = 0;
    string startPlanet, endPlanet;

    cin >> planetsCount >> portalsCount;

    OpenHashImp<string, int>* hash = new OpenHashImp<string, int>(planetsCount, hash3);
    Graph* graph = new AdjacencyList(planetsCount, true, false);

    int index = 1;

    for (int i = 0; i < portalsCount; i++)
    {
        string planet1, planet2;
        int energyCost;

        cin >> planet1 >> planet2 >> energyCost;

        if (!hash->contains(planet1))
        {
            hash->insert(planet1, index);
            index++;
        }
        
        if (!hash->contains(planet2))
        {
            hash->insert(planet2, index);
            index++;
        }
 
        int indexPlanet1 = hash->get(planet1);
        int indexPlanet2 = hash->get(planet2);
 
        graph->addEdge(indexPlanet1, indexPlanet2, energyCost);
    }

    cin >> startPlanet >> endPlanet;

    int minEnergy = minEnergyBetweenPlanets(graph, hash, startPlanet, endPlanet);

    cout << minEnergy << endl;

    delete graph;
    delete hash;

    return 0;
}