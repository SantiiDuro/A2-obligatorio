#ifndef OPENHASH_IMP
#define OPENHASH_IMP

#include "OpenHash.h"

template <class K, class V>
class OpenHashImp : public OpenHash<K, V> 
{
public:
    OpenHashImp(int expected, int (*hashFunc)(K))
    {
        size = nextPrime(2 * expected);   
        table = new node*[size];
        count = 0;
        for(int i = 0; i < size; i++) table[i] = NULL;
        hashFunction = hashFunc;
    }

    ~OpenHashImp()
    {
        for(int i = 0; i < size; i++)
        {
            node* current = table[i];
            while(current != NULL)
            {
                node* toDelete = current;
                current = current->next;
                delete toDelete;
            }
        }
        delete[] table;
    }

    void insert(K key, V value)
    {
        int index = abs(hashFunction(key) % size);
        if(!contains(key))
        {
            node* newNode = new node(key, value);
            newNode->next = table[index];
            table[index] = newNode;
            count++;
        } 
        else
        {
            node* current = table[index];
            while(current != NULL)
            {
                if(current->key == key)
                {
                    current->value = value;
                    return;
                }
                current = current->next;
            }
        }
    }

    V get(K key)
    {
        int index = abs(hashFunction(key) % size);
        node* current = table[index];
        while(current != NULL)
        {
            if(current->key == key) return current->value;
            current = current->next;
        }

        return V();
    }

    bool contains(K key)
    {
        int index = abs(hashFunction(key) % size);
        node* current = table[index];
        while(current != NULL)
        {
            if(current->key == key) return true;
            current = current->next;
        }   
        return false; 
    }

    void remove(K key)
    {
        int index = abs(hashFunction(key) % size);
        node* current = table[index];
        node* prev = NULL;
        while(current != NULL)
        {
            if(current->key == key)
            {
                if(prev == NULL) table[index] = current->next;
                else prev->next = current->next;
                delete current;
                count--;
                return;
            }
            prev = current;
            current = current->next;
        }
    }

private:
    struct node
    {
        K key;
        V value;
        node* next;
        node(K k, V v) : key(k), value(v), next(NULL) {}
    };

    node** table;
    int size;
    int count;
    int (*hashFunction)(K);

    bool isPrime(int num)
    {
        if (num < 2) return false;
        for (int i = 2; i * i <= num; i++)
        {
            if (num % i == 0) return false;
        }
        return true;
    }

    int nextPrime(int num)
    {
        while (!isPrime(num)) num++;
        return num;
    }
};

#endif