#ifndef MASSOCIATIVEARRAY_H
#define MASSOCIATIVEARRAY_H

#include "mshareddataptr.h"
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

    /**
     * Inserts @param value value for @param key key.
     * @note In order to guarantee constant time
     * insertion this method does not check
     * for existing keys. This can lead to multiple
     * values with the same keys to be stored.
     * Check with hasKey or use operator[] if you
     * want to avoid this behavior.
     */
    void insert(const K &key, const T &value);
    T value(const K& key) const;

    MList<T> values(const K& key) const;

    T pick(const K& key);
    MList<T> pickAll(const K& key);

    int size() const;

    bool hasKey(const K& key) const;

    T& operator[](const K& key);

private:
    template<typename K, typename V>
    class MAssociativeArrayPrivate;

    MSharedDataPtr<MAssociativeArrayPrivate<K, V> > d;
};

template<typename K, typename V>
class MAssociativeArray::MAssociativeArrayPrivate
{
public:
    MAssociativeArrayPrivate(MAssociativeArray<K, V> *m)
        : m(m),
          size(0)
    {}

    MAssociativeArrayPrivate(const MAssociativeArrayPrivate<K, V>& copy)
        : m(copy.m),
          values(copy.values)
    {}

    MAssociativeArray *m;
    MList<MPair<K, V> > values;
};

template<typename K, typename V>
MAssociativeArray<K,V>::MAssociativeArray() :
    d(new MAssociativeArrayPrivate<K, V>(this))
{
}

template<typename K, typename V>
MAssociativeArray<K,V>::MArrociativeArray(const MAssociativeArray<K, V>& copy) :
    d(copy.d)
{}

template<typename K, typename V>
MAssociativeArray<K,V>::~MAssociativeArray()
{}

template<typename K, typename V>
int MAssociativeArray<K,V>::size() const
{
    return d->values.size();
}

template<typename K, typename V>
bool MAssociativeArray<K,V>::hasKey(const K &key) const
{
    MList<MPair<K,V> >::ConstIterator it = d->values.constBegin();
    for (; it != d->values.constEnd(); ++it) {
        if (it.value().left == key) {
            return true;
        }
    }

    return false;
}

template<typename K, typename V>
void MAssociativeArray<K,V>::insert(const K &key, const T &value)
{
    d->values.append(MPair<K, V>(key, value));
}

template<typename K, typename V>
V& MAssociativeArray<K,V>::operator[](const K& key)
{
    MList<MPair<K,V> >::Iterator it = d->values.begin();

    for (; it != d->values.end(); ++it) {
        MPair<K,V> &item = it.value();
        if (item.left == key) {
            return item.right;
        }
    }

    d->values.append(MPair<K,V>(key, value));
    return d->values[d->values.size() - 1];
}

template<typename K, typename V>
V MAssociativeArray<K,V>::value(const K &key) const
{
    MList<MPair<K,V> >::ConstIterator it = d->values.constBegin();

    for (; it != d->values.constEnd(); ++it) {
        MPair<K,V> &item = it.value();
        if (item.left == key) {
            return item.right;
        }
    }

    return V();
}

template<typename K, typename V>
MList<V> MAssociativeArray<K, V>::values(const K& key) const
{
    MList<V> list;
    MList<MPair<K,V> >::ConstIterator it = d->values.constBegin();
    for (; it != d->values.end(); ++it) {
        if (it.value().left == key) {
            list.append(it.value().right);
        }
    }

    return list;
}

/*template<typename K, typename V>
T MAssociativeArray<K,V>::pick(const K& key)
{
    MList<MPair<K,V> >::ConstIterator it = d->values.constBegin();
    for (; it != d->values.end(); ++it) {
        if (it.value().left == key) {
            list.append(it.value().right);
        }
    }

    return T();
}*/

MList<T> pickAll(const K& key);

#endif // MASSOCIATIVEARRAY_H
