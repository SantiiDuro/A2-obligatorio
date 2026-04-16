#ifndef HASH_H
#define HASH_H

template <class K, class V>
class Hash
{
public:
    virtual ~Hash() {}
    virtual void insert(K key, V value) = 0;
    virtual V get(K key) = 0;
    virtual bool contains(K key) = 0;
    virtual void remove(K key) = 0;
};

#endif