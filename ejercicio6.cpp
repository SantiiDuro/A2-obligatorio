#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "tads/BinaryHeap.h"
#include "tads/BinaryHeapImp.cpp"

using namespace std;

struct Coordinates
{
    int x;
    int y;
    Coordinates() : x(0), y(0) {}
    Coordinates(int _x, int _y) : x(_x), y(_y) {}
};

bool coordComparatorX(Coordinates c1, Coordinates c2)
{
     return c1.x < c2.x;
}

bool coordComparatorY(Coordinates c1, Coordinates c2)
{
     return c1.y < c2.y;
}

long long distanceEquationSquared(Coordinates c1, Coordinates c2)
{
    long long dx = (long long)c1.x - c2.x;
    long long dy = (long long)c1.y - c2.y;

    return dx*dx + dy*dy;
}

bool isCriticalInStripY(Coordinates* points, int from, int to, int mid, long long D, long long D2)
{
    HeapImp<Coordinates> minHeap((to-from) + 2, coordComparatorY);
    Coordinates* strip = new Coordinates[(to-from) + 2]();
    
    int cantElementsInStrip = 0;
    int midX = points[mid].x;

    for (int i = from; i <= to; i++)
    {
        int posInX = points[i].x;
        if (abs((long long)posInX - midX) <= D)
        {
            minHeap.insert(points[i]);
            cantElementsInStrip++;
        }
    }

    for (int i = 1; i <= cantElementsInStrip; i++)
    {
        strip[i] = minHeap.top();
        minHeap.removeTop();
    }

    for (int i = 1; i <= cantElementsInStrip; i++)
    {
        for (int j = i + 1; j <= cantElementsInStrip; j++)
        {
            int posInYI = strip[i].y;
            int posInYJ = strip[j].y;

            if (((long long)posInYJ - posInYI) > D) break;

            long long distance = distanceEquationSquared(strip[i], strip[j]);

            if (distance <= D2) return true;
        }
    }

    delete[] strip;

    return false;
}

bool isCritical(Coordinates* points, int from, int to, long long D, long long D2)
{
    if ((to - from) <= 2)
    {
        for (int i = from; i <= to; i++)
        {
            for (int j = i+1; j <= to; j++)
            {
                long long distance = distanceEquationSquared(points[i], points[j]);

                if (distance <= D2) return true;
            }
        }

        return false;
    }

    int mid = (from + to)/2;

    if (isCritical(points, from, mid, D, D2)) return true;
    if (isCritical(points, mid + 1, to, D, D2)) return true;

    return isCriticalInStripY(points, from, to, mid, D, D2);
}

int main()
{
    int cantFocosDetectados = 0;
    long long distaciaUmbral = 0;

    cin >> cantFocosDetectados >> distaciaUmbral;

    HeapImp<Coordinates> minHeap(cantFocosDetectados, coordComparatorX);
    Coordinates* points = new Coordinates[cantFocosDetectados + 1]();

    for (int i = 0; i < cantFocosDetectados; i++)
    {
        int x, y = 0;
        Coordinates c;

        cin >> x >> y;

        c = Coordinates(x, y);
        minHeap.insert(c);
    }

    for (int i = 1; i <= cantFocosDetectados; i++)
    {
        points[i] = minHeap.top();
        minHeap.removeTop();
    }

    long long distaciaUmbralCuadrada = distaciaUmbral*distaciaUmbral;

    bool result = isCritical(points, 1, cantFocosDetectados, distaciaUmbral, distaciaUmbralCuadrada);

    string resultStr = result ? "true" : "false";
    
    cout << resultStr << endl;
    
    delete[] points;

    return 0;
}