#ifndef QUEUE_H
#define QUEUE_H
 
template <class T>
class Queue
{
public:
    virtual ~Queue() {}
    virtual void enqueue(T element) = 0;
    virtual T dequeue() = 0;
    virtual bool isEmpty() = 0;
};
 
#endif
 