#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "tads/BinaryHeap.h"
#include "tads/BinaryHeapImp.cpp"

using namespace std;

struct Patient
{
    int id;
    int arrivalTime;
    int urgencyLevel;
    int insertionOrder;
};

bool patientComparator(Patient p1, Patient p2)
{
    if (p1.urgencyLevel != p2.urgencyLevel)
    {
        return p1.urgencyLevel > p2.urgencyLevel;
    }
    if (p1.arrivalTime != p2.arrivalTime)
    {
        return p1.arrivalTime < p2.arrivalTime;
    }

    return p1.insertionOrder < p2.insertionOrder;
}

int main()
{
    int patientsCount = 0;

    cin >> patientsCount;

    HeapImp<Patient> emergencyQueue(patientsCount, patientComparator);

    for (int i = 0; i < patientsCount; i++)
    {
        Patient p;
        cin >> p.id >> p.arrivalTime >> p.urgencyLevel;
        p.insertionOrder = i;
        emergencyQueue.insert(p);
    }

    while (!emergencyQueue.isEmpty())
    {
        Patient next = emergencyQueue.top();
        emergencyQueue.removeTop();
        cout << next.id << endl;
    }

    return 0;
}