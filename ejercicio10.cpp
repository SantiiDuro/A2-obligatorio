#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;

bool isSolution(int* cardsValue, int cantCards, int objValue)
{
    if (cantCards == 1) return cardsValue[0] == objValue;

    return false;
}

bool isValidMove(int a, int b, char operation)
{
    if (operation == '/') return ((b != 0) && (a % b == 0));
    if (operation == '-') return (a > b);

    return true;
}

void applyMove(int* cardsValue, int cantCards, int* aux, int posA, int posB, char op)
{
    int a = cardsValue[posA];
    int b = cardsValue[posB];
    int c = 0;
    
    if (op == '+') c = a + b;
    else if (op == '-') c = a - b;
    else if (op == '*') c = a * b;
    else c = a / b;
    
    int posAux = 0;
    for (int i = 0; i < cantCards; i++)
    {
        if (i == posA || i == posB) continue;

        aux[posAux] = cardsValue[i];
        posAux++;
    }

    aux[posAux] = c;
}

void numbersRoundBT(int* cardsValue, int cantCards, int objValue, bool& foundSolution)
{
    if (!foundSolution)
    {
        if (isSolution(cardsValue, cantCards, objValue))
        {
            foundSolution = true;
        }
        else
        {
            char operations[] = {'+', '-', '*', '/'};

            for (int i = 0; i < cantCards; i++)
            {
                for (int j = 0; j < cantCards; j++)
                {
                    if (i == j) continue;
                    
                    for (int k = 0; k < 4; k++)                    
                    {
                        char op = operations[k];
                        int a = cardsValue[i];
                        int b = cardsValue[j];

                        if (isValidMove(a, b, op))
                        {
                            int* aux = new int[cantCards - 1]();
                            applyMove(cardsValue, cantCards, aux, i, j, op);
                            numbersRoundBT(aux, cantCards - 1, objValue, foundSolution);
                            
                            delete[] aux;
                        }
                    }
                }
            }
        }
    }
}

int main()
{
    int cantCards = 0, objValue = 0;
    bool foundSolution = false;
    
    cin >> cantCards;

    int* cardsValue = new int[cantCards]();

    for (int i = 0; i < cantCards; i++)
    {
        cin >> cardsValue[i]; 
    }
    
    cin >> objValue;

    numbersRoundBT(cardsValue, cantCards, objValue, foundSolution);

    cout << (foundSolution ? 1 : 0) << endl;

    delete[] cardsValue;

    return 0;
}