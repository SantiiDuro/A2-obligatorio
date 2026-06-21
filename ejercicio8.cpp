#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;

string greedySolution(string chain)
{
    int* arr = new int[26]();
    int R = chain.length();
    string sol = "";
    
    for (int i = 0; i < R; i++)
    {
        int position = (int)chain[i] - 97;
        arr[position]++;
    }
    
    int i = 25, M = 0, posM = 0, posSol = -1;;
    bool holgura = false;

    while (R > 0)
    {
        if (arr[i] == 0)
        {
            i--;
            continue;
        }

        M = 0, posM = 0;
        for (int j = 0; j <= i; j++)
        {
            if (M < arr[j])
            {
                M = arr[j];
                posM = j;
            }
        }

        if ((R + 1) < (2 * M)) return "Imposible";

        holgura = (R + 1) > (2 * M);

        if (holgura)
        {
            if (posSol == -1 || sol[posSol] != (char)(i + 97))
            {
                sol += (char)(i + 97);
                arr[i]--;
                R--;
                posSol++;
            }
            else
            {
                for (int j = i - 1; j >= 0; j--)
                {
                    if (arr[j] == 0) continue;

                    sol += (char)(j + 97);
                    arr[j]--;
                    R--;
                    posSol++;
                    break;
                }
            }
        }
        else
        {
            sol += (char)(posM + 97);
            arr[posM]--;
            R--;
            posSol++;
        }
    }
    
    delete[] arr;

    return sol;
}

int main()
{
    string chain, sol;

    cin >> chain;
    
    sol = greedySolution(chain);

    cout << sol << endl;

    return 0;
}