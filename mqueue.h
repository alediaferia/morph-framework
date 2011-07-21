#ifndef MQUEUE_H
#define MQUEUE_H

#include "mlist.h"

template <typename T>
class MQueue : public MList<T>
{
public:
    MQueue() : MList<T>()
    {}

    void enqueue(const T& t);
    T dequeue();
};

template <typename T>
void MQueue<T>::enqueue(const T &t)
{
    this->append(t);
}

template <typename T>
T MQueue<T>::dequeue()
{
    return this->pickAt(0);
}

#endif // MQUEUE_H
