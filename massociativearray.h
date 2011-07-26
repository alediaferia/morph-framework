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

    /**
     * returns the value for the specified
     * key. If no value is stored for the
     * specified key a default-constructed
     * one is returned
     */
    T value(const K& key) const;

    /**
     * Returns a list for all the values
     * stored with the specified key.
     */
    MList<T> values(const K& key) const;

    /**
     * Returns all values in the array.
     */
    MList<T> values() const;

    /**
     * Takes the value for the specified
     * key from the array and removes
     * it from the container.
     */
    T pick(const K& key);
    MList<T> pickAll(const K& key);

    int size() const;

    bool hasKey(const K& key) const;

    /**
     * Accesses the value identified by
     * the specified key. If no value
     * is present with the specified key default constructed
     * one is inserted into the array and a reference
     * to it is returned.
     */
    T& operator[](const K& key);

private:
    class MAssociativeArrayPrivate;
    MSharedDataPtr<MAssociativeArrayPrivate> d;
};

template<typename K, typename T>
class MAssociativeArray<K,T>::MAssociativeArrayPrivate
{
public:
    MAssociativeArrayPrivate(MAssociativeArray<K,T> *m)
        : m(m)
    {}

    MAssociativeArrayPrivate(const MAssociativeArrayPrivate& copy)
        : m(copy.m),
          values(copy.values)
    {}

    MAssociativeArray *m;
    MList<MPair<K,T> > values;
};

template<typename K, typename T>
MAssociativeArray<K,T>::MAssociativeArray() :
    d(new MAssociativeArrayPrivate(this))
{
}

template<typename K, typename T>
MAssociativeArray<K,T>::MAssociativeArray(const MAssociativeArray<K,T>& copy) :
    d(copy.d)
{}

template<typename K, typename T>
MAssociativeArray<K,T>::~MAssociativeArray()
{}

template<typename K, typename T>
int MAssociativeArray<K,T>::size() const
{
    return d->values.size();
}

template<typename K, typename T>
bool MAssociativeArray<K,T>::hasKey(const K &key) const
{
    typename MList<MPair<K,T> >::ConstIterator it = d->values.constBegin();
    for (; it != d->values.constEnd(); ++it) {
        if (it.value().left == key) {
            return true;
        }
    }

    return false;
}

template<typename K, typename T>
void MAssociativeArray<K,T>::insert(const K &key, const T &value)
{
    d->values.append(MPair<K,T>(key, value));
}

template<typename K, typename T>
T& MAssociativeArray<K,T>::operator[](const K& key)
{
    typename MList<MPair<K,T> >::Iterator it = d->values.begin();

    for (; it != d->values.end(); ++it) {
        if (it.value().left == key) {
            return it.value().right;
        }
    }

    d->values.append(MPair<K,T>(key, T()));
    return d->values[d->values.size() - 1].right;
}

template<typename K, typename T>
T MAssociativeArray<K,T>::value(const K &key) const
{
    typename MList<MPair<K,T> >::ConstIterator it = d->values.constBegin();

    for (; it != d->values.constEnd(); ++it) {
        MPair<K,T> item = it.value();
        if (item.left == key) {
            return item.right;
        }
    }

    return T();
}

template<typename K, typename T>
MList<T> MAssociativeArray<K,T>::values(const K& key) const
{
    MList<T> list;
    typename MList<MPair<K,T> >::ConstIterator it = d->values.constBegin();
    for (; it != d->values.end(); ++it) {
        if (it.value().left == key) {
            list.append(it.value().right);
        }
    }

    return list;
}

template<typename K, typename T>
T MAssociativeArray<K,T>::pick(const K& key)
{
    typename MList<MPair<K,T> >::ConstIterator it = d->values.constBegin();
    for (; it != d->values.end(); ++it) {
        if (it.value().left == key) {
            T data = it.value().right;
            d->values.remove(it);
            return data;
        }
    }

    return T();
}

template<typename K, typename T>
MList<T> MAssociativeArray<K,T>::pickAll(const K& key)
{
    MList<T> list;

    typename MList<MPair<K,T> >::ConstIterator it = d->values.constBegin();
    for (; it != d->values.end(); ++it) {
        if (it.value().left == key) {
            T data = it.value().right;
            it = d->values.remove(it);
            list.append(data);
        }
    }

    return list;
}

template<typename K, typename T>
MList<T> MAssociativeArray<K,T>::values() const
{
    MList<T> list;

    typename MList<MPair<K,T> >::ConstIterator it = d->values.constBegin();
    for (; it != d->values.constEnd(); ++it) {
        list.append(it.value().right);
    }

    return list;
}

#endif // MASSOCIATIVEARRAY_H
