#include "mqueue.h"

MQueue::MQueue() : MList()
{}

void MQueue::enqueue(mref t)
{
    this->append(t);
}

mref MQueue::dequeue()
{
    return this->pickAt(0);
}
