#ifndef MQUEUE_H
#define MQUEUE_H

#include "mlist.h"

class MQueue : public MList
{
    M_OBJECT(MQueue)
public:
    MQueue();

    void enqueue(mref t);
    mref dequeue();
};



#endif // MQUEUE_H
