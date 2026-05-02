#ifndef NODE_LIST
#define NODE_LIST

template <class T>
struct NodeList
{
    T element;
    NodeList* next;

    NodeList(T _element, NodeList* _next = NULL)
    {
        element = _element;
        next = _next;
    }
};

#endif