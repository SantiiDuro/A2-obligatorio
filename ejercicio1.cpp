#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "tads/OpenHash.h"
#include "tads/OpenHashImp.cpp"

using namespace std;

int charHash(char c)
{
    return (int) c;
}

int solAccesoLab(int cantSalas, string cadena)
{
    OpenHashImp<char, int>* hash = new OpenHashImp<char, int>(cantSalas - 1, charHash);
    int additional = 0;

    for(int i = 0; i < 2*cantSalas - 2; i += 2)
    {
        char key = cadena[i];
        char door = cadena[i + 1];
        char needed = tolower(door);

        if(hash->contains(key)) hash->insert(key, hash->get(key) + 1);
        else hash->insert(key, 1);

        if(hash->contains(needed)) 
        {
            int count = hash->get(needed);
            if(count == 1) hash->remove(needed);
            else hash->insert(needed, count - 1);
        } 
        else additional++;
    }

    delete hash;
    return additional;
}

int main()
{
    int cantSalas, cantLlavesAdicionales = 0;
    string cadena;

    cin >> cantSalas;
    cin >> cadena;

    cantLlavesAdicionales = solAccesoLab(cantSalas, cadena);

    cout << cantLlavesAdicionales << endl;

    return 0;
}