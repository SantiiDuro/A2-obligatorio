#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "funciones/merge_sort.cpp"
#include "tads/Competitior.cpp"

using namespace std;

int main()
{
    int cantCompetitors, time = 0;

    cin >> cantCompetitors;

    Competitior* times = new Competitior[cantCompetitors + 1]();
    Competitior* aux = new Competitior[cantCompetitors + 1]();

    for (int i = 0; i < 3; i++)
    {
        for (int j = 1; j <= cantCompetitors; j++)
        {
            cin >> time;

            times[j].index = j;
            times[j].time += time;
        }
    }
    
    mergeSort(times, aux, 1, cantCompetitors);

    for (int i = 1; i <= cantCompetitors; i++)
    {
        cout << times[i].index << endl;
    }

    delete[] times;

    return 0;
}