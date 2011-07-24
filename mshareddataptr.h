#ifndef MSHAREDDATAPTR_H
#define MSHAREDDATAPTR_H

#include <iostream>

/**
 * This class acts similarly to MSharedPtr
 * but makes working with shared data easier.
 * When the data pointed to by this class
 * is going to be modified a deep copy is
 * performed and the current pointer is detached.
 * The detach is not performed when the current
 * reference count is not greater than 1.
 * @note The data pointed to by this class
 * must be copyable.
 */

template<typename T>
class MSharedDataPtr
{
public:
    MSharedDataPtr() :
        d(new PrivateSharedPtr<T>(this))
    {}

    MSharedDataPtr(T* ptr) :
        d(new PrivateSharedPtr<T>(this))
    {
        d->refCount = 1;
        d->ptr = ptr;
    }

    MSharedDataPtr(const MSharedDataPtr<T> &copy) :
        d(copy.d)
    {
        d->refCount += 1;
    }

    ~MSharedDataPtr()
    {
        d->deref();
    }

    T* data()
    {
        detach();
        return d->ptr;
    }

    const T* data() const
    {
        return d->ptr;
    }

    T* operator->()
    {
        detach();
        return d->ptr;
    }

    const T* operator->() const
    {
        return d->ptr;
    }

    T& operator*()
    {
        detach();
        return *(d->ptr);
    }

    const T& operator*() const
    {
        return *(d->ptr);
    }

    MSharedDataPtr<T>& operator=(const MSharedDataPtr& copy)
    {
       d->deref();
       d = copy.d;
       d->refCount++;
    }

    int refCount() const
    {
        return d->refCount;
    }

    void detach()
    {
        if (d->refCount == 1) {
            return;
        }

        //std::cout << "detaching..." << std::endl;
        PrivateSharedPtr<T> *newDPtr = new PrivateSharedPtr<T>(this);
        newDPtr->ptr = (T*)malloc(sizeof(T));
        *newDPtr->ptr = *d->ptr;
        newDPtr->refCount = 1;

        d->deref();
        d = newDPtr;
    }

private:
    template <typename X>
    class PrivateSharedPtr {
    public:
        PrivateSharedPtr(MSharedDataPtr<X> *m) :
            m(m),
            refCount(0),
            ptr(0)
        {}

        void deref()
        {
            --this->refCount;
            //std::cout << "refcount " << this->refCount << std::endl;

            if(!this->refCount) {
                //std::cout << "freeing data" << std::endl;
                delete ptr;
                delete this;
            }
        }

        MSharedDataPtr<X> *m;
        unsigned int refCount;
        T* ptr;
    };

    PrivateSharedPtr<T>* d;
};

#endif // MSHAREDDATAPTR_H
