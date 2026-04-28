#ifndef BINARYHEAP_H
#define BINARYHEAP_H

template <class T>
class Heap 
{
public:
    virtual ~Heap() {}
    virtual void insert(T element) = 0;
    virtual T top() = 0;
    virtual void removeTop() = 0;
    virtual bool isEmpty() = 0;
    virtual bool isFull() = 0;
};

#endif