#ifndef MASSOCIATIVEARRAY_H
#define MASSOCIATIVEARRAY_H

#include "msharedptr.h"
#include "mlist.h"
#include "mpair.h"

/**
 * This class provides a simple
 * unsorted associative array that
 * can be used with any data type.
 * Insertion takes constant time while
 * search takes linear time.
 */

template<typename K, typename T>
class MAssociativeArray
{
public:
    MAssociativeArray();
    MAssociativeArray(const MAssociativeArray &);
    ~MAssociativeArray();

    void insert(const K &key, const T &value);
    T value(const K& key);

    T pick(const K& key);

    int size() const;

    T& operator[](const K& key);

private:
    template<typename K, typename V>
    class MAssociativeArrayPrivate;

    MAssociativeArrayPrivate<K, V> *const d;
};

template<typename K, typename V>
class MAssociativeArray::MAssociativeArrayPrivate
{
public:
    MAssociativeArrayPrivate(MAssociativeArray<K, V> *m)
        : m(m),
          size(0)
    {}

    MAssociativeArray *m;
    MList<MPair<K, V> > values;
    int size;
};

template<typename K, typename V>
MAssociativeArray::MAssociativeArray() :
    d(new MAssociativeArrayPrivate<K, V>(this))
{
}

template<typename K, typename V>
MAssociativeArray::MArrociativeArray(const MAssociativeArray<K, V>& copy) :
    d(copy.d)
{}

template<typename K, typename V>
MAssociativeArray::~MAssociativeArray()
{}

template<typename K, typename V>
int MAssociativeArray::size() const
{
    return d->size;
}

template<typename K, typename V>
void MAssociativeArray::insert(const K &key, const T &value)
{
}

#endif // MASSOCIATIVEARRAY_H
