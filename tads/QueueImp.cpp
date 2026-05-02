#ifndef QUEUE_IMP
#define QUEUE_IMP

#include <cassert>
#include "Queue.h"

template <class T>
class QueueImp : public Queue<T>
{
public:
    QueueImp()
    {
        first = NULL;
        last = NULL;
        count = 0;
    }

    ~QueueImp()
    {
        while (!isEmpty())
        {
            dequeue();
        }
    }

    void enqueue(T element)
    {
        Node* newNode = new Node(element);
        
        if (isEmpty())
        {
            first = newNode;
            last = newNode;
        }
        else
        {
            last->next = newNode;
            last = newNode;
        }
        
        count++;
    }

    T dequeue()
    {
        assert(!isEmpty());
        
        Node* temp = first;
        T element = first->data; 
        first = first->next;
        
        if (first == NULL)
        {
            last = NULL;
        }
        
        count--;
        delete temp;
        
        return element;
    }

    bool isEmpty()
    {
        return first == NULL;
    }

private:
    struct Node
    {
        T data;
        Node* next;
        
        Node(T _data) : data(_data), next(NULL) {}
    };
    
    Node* first;
    Node* last;
    int count;
};

#endif