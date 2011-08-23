#ifndef MPAIR_H
#define MPAIR_H

#include "mobject.h"

class MPair : public MObject
{
    M_OBJECT(MPair)
public:
    MPair();
    MPair(mref left, mref right);
    ~MPair();

    static MPair::MRef alloc(mref left, mref right);

    mref left;
    mref right;

    //MPair<V1, V2>& operator=(const MPair<V1, V2> &other);
};

#endif // MPAIR_H
