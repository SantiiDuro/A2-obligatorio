#ifndef OPENHASH_H
#define OPENHASH_H

template <class K, class V>
class OpenHash
{
public:
    virtual ~OpenHash() {}
    virtual void insert(K key, V value) = 0;
    virtual V get(K key) = 0;
    virtual bool contains(K key) = 0;
    virtual void remove(K key) = 0;
};

#endif