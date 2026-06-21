#ifndef MERGE_SORT_IMP
#define MERGE_SORT_IMP
#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "../tads/Competitior.cpp"

void merge(Competitior* arr, Competitior* aux, int from, int mid, int to)
{
    for (int i = from; i <= to; i++)
    {
        aux[i] = arr[i];
    }
    
    int i = from, j = mid + 1, k = from;
    while (i <= mid && j <= to)
    {
        if (aux[i].time <= aux[j].time) 
        {
            arr[k] = aux[i];
            k++;
            i++;
        } 
        else
        {
            arr[k] = aux[j];
            k++;
            j++;
        }
    }

    while (i <= mid) {
        arr[k] = aux[i];
        k++;
        i++;
    }

    while (j <= to) {
        arr[k] = aux[j];
        k++;
        j++;
    }
}

void mergeSort(Competitior* arr, Competitior* aux, int from, int to)
{
    if (from == to) return;

    int mid = (from + to)/2;
    int size1 = mid - from + 1;
    int size2 = to - mid;

    mergeSort(arr, aux, from, mid);
    mergeSort(arr, aux, mid + 1, to);

    merge(arr, aux, from, mid, to);
}

#endif