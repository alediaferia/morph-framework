#ifndef MSOCKET_H
#define MSOCKET_H

#include "mobject.h"
class MSocket : public MObject
{
    M_PROPERTY(MString, ip)
    M_PROPERTY(uint16_t, port)

    MSocket();
    virtual ~MSocket();

    virtual MString read(int size) = 0;
    virtual int write(const MString &) = 0;
};

#endif // MSOCKET_H
