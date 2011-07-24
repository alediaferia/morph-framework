#ifndef MSHAREDPTR_H
#define MSHAREDPTR_H

#include <iostream>

template<typename T>
class PrivateSharedPtr;

/**
 * @class MSharedPtr
 * @author Alessandro Diaferia
 *
 * This template class implements the Shared Pointer pattern.
 * In order to use this class you have to specify the
 * object type and eventually initialize it with a valid pointer.
 * From that time on, in order for the object to work properly,
 * every further interaction with the pointer has to be performed
 * through this class.
 * When the MSharedPtr object goes out of scope the internal
 * refcount to the data gets decremented and when it reaches 0
 * the data itself gets destroyed.
 *
 * @code
   MObject *o = new MObject;
   MSharedPtr<MObject> objectPtr(o);
   // now every further access to the object
   // has to be done through the objectPtr object.
   // this way the ref counting happens correctly
   // and data will be released when appropriate.
   objectPtr->delegate = new MyDelegate.
 * @endcode
 */

template<typename T>
class MSharedPtr
{
public:
    MSharedPtr() :
        d(new PrivateSharedPtr<T>(this))
    {}

    MSharedPtr(T* ptr) :
        d(new PrivateSharedPtr<T>(this))
    {
        d->refCount = 1;
        d->ptr = ptr;
    }

    MSharedPtr(const MSharedPtr<T> &copy) :
        d(copy.d)
    {
        d->refCount += 1;
    }

    ~MSharedPtr()
    {
        d->deref();
    }

    T* data() const
    {
        return d->ptr;
    }

    T* operator->() const
    {
        return d->ptr;
    }

    T& operator*() const
    {
        return *(d->ptr);
    }

    MSharedPtr<T>& operator=(const MSharedPtr& copy)
    {
       d->deref();
       d = copy.d;
       d->refCount++;
    }

    int refCount() const
    {
        return d->refCount;
    }

private:
    template <typename X>
    class PrivateSharedPtr {
    public:
        PrivateSharedPtr(MSharedPtr<X> *m) :
            m(m),
            refCount(0),
            ptr(0)
        {}

        void deref()
        {
            if(!--this->refCount) {
                //std::cout << "freeing data" << std::endl;
                delete ptr;
                delete this;
            }
        }

        MSharedPtr<X> *m;
        unsigned int refCount;
        T* ptr;
    };

    PrivateSharedPtr<T>* d;
};

#endif // MSHAREDPTR_H
