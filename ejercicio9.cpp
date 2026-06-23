#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;

int cantObj = 0, maxWeight = 0, maxVol = 0, maxCost = 0, maxCantSurv = 0, maxCantFood = 0;

struct Object
{
    int weight;
    int volume;
    int cost;
    int value;
    string category;

    Object() : weight(0), volume(0), cost(0), value(0), category(" ") {}
    Object(int _w, int _vol, int _cost, int _va, string _cat) 
        : weight(_w), volume(_vol), cost(_cost), value(_va), category(_cat) {}
};

struct Solution
{
    int maxValue;
    int totalWeight;
    int cantObj;

    Solution() : maxValue(0), totalWeight(0), cantObj(0) {}
    Solution(int _v, int _w, int _o) : maxValue(_v), totalWeight(_w), cantObj(_o) {}
};

bool isBetterSol(Solution s1, Solution s2)
{
    if (s1.maxValue != s2.maxValue) return s1.maxValue > s2.maxValue;
    if (s1.totalWeight != s2.totalWeight) return s1.totalWeight < s2.totalWeight;
    return s1.cantObj < s2.cantObj;
}

Solution bag_01(Object* objects)
{
    Solution****** tab = new Solution*****[cantObj + 1];
	for (int o = 0; o <= cantObj; o++)
	{
        tab[o] = new Solution****[maxWeight + 1]();
        for (int w = 0; w <= maxWeight; w++)
        {
            tab[o][w] = new Solution***[maxVol + 1]();
            for (int v = 0; v <= maxVol; v++)
            {
                tab[o][w][v] = new Solution**[maxCost + 1]();
                for (int c = 0; c <= maxCost; c++)
                {
                    tab[o][w][v][c] = new Solution*[maxCantSurv + 1]();
                    for (int cantS = 0; cantS <= maxCantSurv; cantS++)
                    {
                        tab[o][w][v][c][cantS] = new Solution[maxCantFood + 1]();
                    }                  
                }
            }
        }
	}

    for (int indexObj = 1; indexObj <= cantObj; indexObj++)
    {
        int weightObj = objects[indexObj].weight;
        int volumeObj = objects[indexObj].volume;
        int costObj = objects[indexObj].cost;
        int valueObj = objects[indexObj].value;
        bool isFood = objects[indexObj].category == "comida";

        for (int indexW = 0; indexW <= maxWeight; indexW++)
            for (int indexV = 0; indexV <= maxVol; indexV++)
                for (int indexC = 0; indexC <= maxCost; indexC++)
                    for (int indexCS = 0; indexCS <= maxCantSurv; indexCS++)
                        for (int indexCF = 0; indexCF <= maxCantFood; indexCF++)
                        {
                            bool categorySpace = isFood ? (indexCF >= 1) : (indexCS >= 1);

                            if (weightObj <= indexW && volumeObj <= indexV && costObj <= indexC && categorySpace)
                            {
                                int cantS = isFood ? indexCS : indexCS - 1;
                                int cantF = isFood ? indexCF - 1 : indexCF;
                                
                                Solution before = tab[indexObj - 1][indexW - weightObj][indexV - volumeObj]
                                                    [indexC - costObj][cantS][cantF];
                                Solution usingObj(before.maxValue + valueObj, before.totalWeight + weightObj, 
                                                    before.cantObj + 1);
                                Solution notUsingObj = tab[indexObj - 1][indexW][indexV][indexC][indexCS][indexCF];

                                tab[indexObj][indexW][indexV][indexC][indexCS][indexCF] =
                                    isBetterSol(usingObj, notUsingObj) ? usingObj : notUsingObj;
                            }
                            else
                            {
                                tab[indexObj][indexW][indexV][indexC][indexCS][indexCF] =
                                    tab[indexObj - 1][indexW][indexV][indexC][indexCS][indexCF];
                            }
                        }
    }
    
    return tab[cantObj][maxWeight][maxVol][maxCost][maxCantSurv][maxCantFood];
}

int main()
{
    cin >> cantObj;
    cin >> maxWeight >> maxVol >> maxCost >> maxCantSurv >> maxCantFood;

    Object* objects = new Object[cantObj + 1];
    for (int i = 1; i <= cantObj; i++)
    {
        cin >> objects[i].weight >> objects[i].volume >> objects[i].cost 
            >> objects[i].value >> objects[i].category;
    }

    Solution sol = bag_01(objects);

    cout << sol.maxValue << " " << sol.totalWeight <<  " " << sol.cantObj << endl;

    return 0;
}