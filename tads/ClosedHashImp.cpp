#ifndef CLOSEDHASH_IMP
#define CLOSEDHASH_IMP

#include "Hash.h"
#include "../funciones/enteros.cpp"


template <class K, class V>
class ClosedHashImp : public Hash<K, V> 
{
public:
    ClosedHashImp(int expected, int (*hashFunc1)(K), int (*hashFunc2)(K))
    {
        size = nextPrime(2 * expected);
        table = new node[size];
        count = 0;
        hashFunction1 = hashFunc1;
        hashFunction2 = hashFunc2;
    }

    ~ClosedHashImp()
    {
        delete[] table;
    }

    void insert(K key, V value)
    {
        int i = 0;
        int index = calculateIndex(key, i);
        while(table[index].occupied && !table[index].deleted)
        {
            i++;
            index = calculateIndex(key, i);
        }
        table[index].key = key;
        table[index].value = value;
        table[index].occupied = true;
        table[index].deleted = false;
        count++;
    }

    V get(K key)
    {
        int i = 0;
        int index = calculateIndex(key, i);
        while(table[index].occupied || table[index].deleted)
        {
            if(table[index].occupied && !table[index].deleted && table[index].key == key)
                return table[index].value;       
            i++;
            index = calculateIndex(key, i);
        }
        return V();
    }

    bool contains(K key)
    {
        int i = 0;
        int index = calculateIndex(key, i);
        while (table[index].occupied || table[index].deleted)
        {
            if (table[index].occupied && !table[index].deleted && table[index].key == key)
                return true;
            i++;
            index = calculateIndex(key, i);
        }
        return false;
    }

    void remove(K key)
    {
        int i = 0;
        int index = calculateIndex(key, i);
        while (table[index].occupied || table[index].deleted)
        {
            if (table[index].occupied && !table[index].deleted && table[index].key == key)
            {
                table[index].occupied = false;
                table[index].deleted = true;
                count--;
                return;
            }
            i++;
            index = calculateIndex(key, i);
        }
    }

private:
    struct node
    {
        K key;
        V value;
        bool occupied;
        bool deleted;
        node() : occupied(false), deleted(false) {}
        node(K k, V v) : key(k), value(v), occupied(true), deleted(false) {}
    };

    node* table;
    int size;
    int count;
    int (*hashFunction1)(K);
    int (*hashFunction2)(K);

    int calculateIndex(K key, int tryCount) {
        return abs(hashFunction1(key) + tryCount * hashFunction2(key)) % size;
    }
};

#endif