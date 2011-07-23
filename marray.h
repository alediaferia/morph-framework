#ifndef MARRAY_H
#define MARRAY_H

#include "marray_p.h"

template<typename T>
class MAbstractArrayHelper
{
public:
    virtual T& operator[](int) = 0;
};

template<int capacity, typename T>
class MArrayHelper
{
    T& operator[](int i)
    {
        return m_staticArray[i];
    }

private:
    T m_staticArray[capacity];
};

template<typename T>
class MArray
{
public:
    MArray(int capacity);
    ~MArray();

    T& operator[](int index);

private:
    template<typename X>
    class MArrayPrivate
    {
    public:
        MArrayPrivate(MArray<X> *m, int capacity) :
            m(m),
            helper(new MArrayHelper<capacity, X>())
        {}

        ~MArrayPrivate()
        {
            delete helper;
        }

        MArray *m;
        MAbstractArrayHelper<T> *helper;
    };

    MArrayPrivate<T> *const d;
};

template<typename T>
MArray::MArray(int capacity)
    : d(new MArray::MArrayPrivate<T>(this, capacity))
{}

template<typename T>
MArray::~MArray()
{
    delete d;
}

template<typename T>
T& MArray::operator[](int i) {
    return *d->helper[i];
}

#endif // MARRAY_H
