#ifndef BINARYHEAP_IMP
#define BINARYHEAP_IMP

#include "BinaryHeap.h"

template <class T>
class HeapImp : public Heap<T> 
{
public:
    HeapImp(int _capacity, bool (*_comparator)(T, T))
    {
        nextFree = 1;
        capacity = _capacity + 1;
        arr = new T[capacity]();
        comparator = _comparator;
    }

    ~HeapImp()
    {
        delete[] arr;
    }

    void insert(T element)
    {
        assert(!isFull());
        arr[nextFree] = element;
        nextFree++;
        swim(nextFree - 1);
    }

    T top()
    {
        assert(!isEmpty());
        return arr[1];
    }

    void removeTop()
    {
        assert(!isEmpty());
        nextFree--;
        swap(1, nextFree);
        sink(1);
    }

    bool isFull()
    {
        return nextFree == capacity;
    }

    bool isEmpty()
    {
        return nextFree == 1;
    }

private:
    T* arr;
    int nextFree;
    int capacity;
    bool (*comparator)(T, T);

    int parent(int pos)
    {
        return pos / 2;
    }

    int leftChild(int pos)
    {
        return 2 * pos;
    }

    int rightChild(int pos)
    {
        return (2 * pos) + 1;
    }

    void swap(int pos1, int pos2)
    {
        T aux = arr[pos1];
        arr[pos1] = arr[pos2];
        arr[pos2] = aux;
    }

    void swim(int pos)
    {
        if (pos > 1 && comparator(arr[pos], arr[parent(pos)]))
        {
            swap(pos, parent(pos));
            swim(parent(pos));
        }
    }

    void sink(int pos)
    {
        if (leftChild(pos) < nextFree)
        {
            int smaller = leftChild(pos);
            if (rightChild(pos) < nextFree && comparator(arr[rightChild(pos)], arr[smaller]))
            {
                smaller = rightChild(pos);
            }
            if (comparator(arr[smaller], arr[pos]))
            {
                swap(pos, smaller);
                sink(smaller);
            }
        }
    }
};

#endif