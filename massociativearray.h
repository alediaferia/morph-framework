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

class MAssociativeArray : public MObject
{
    M_OBJECT(MAssociativeArray)
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
    void insert(mref key, mref value);

    /**
     * returns the value for the specified
     * key. If no value is stored for the
     * specified key a default-constructed
     * one is returned
     */
    mref value(mref key) const;

    /**
     * Returns a list for all the values
     * stored with the specified key.
     */
    MList::MRef values(mref key) const;

    /**
     * Returns all values in the array.
     */
    MList::MRef values() const;

    /**
     * Takes the value for the specified
     * key from the array and removes
     * it from the container.
     */
    mref pick(mref key);
    MList::MRef pickAll(mref key);

    int size() const;

    bool hasKey(mref key) const;

    /**
     * Accesses the value identified by
     * the specified key. If no value
     * is present with the specified key default constructed
     * one is inserted into the array and a reference
     * to it is returned.
     */
    mref& operator[](mref key);

private:
    class MAssociativeArrayPrivate;
    MAssociativeArrayPrivate* d;
};

#endif // MASSOCIATIVEARRAY_H
