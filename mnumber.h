#ifndef MNUMBER_H
#define MNUMBER_H

#include "mobject.h"

class MNumber : public MObject
{
    M_OBJECT(MNumber)
public:
    MNumber();

    void setIntValue(int);
    void setUnsignedIntValue(unsigned int);
    void setLongValue(long);
    void setLongLongValue(long long);
    void setUnsignedLongValue(unsigned long);
    void setUnsignedLongLongValue(unsigned long long);
    void setFloatValue(float);

    int intValue() const;
    unsigned int unsignedIntValue() const;
    long longValue() const;
    long long longLongValue() const;
    unsigned long unsignedLongValue() const;
    unsigned long long unsignedLongLongValue() const;
    float floatValue() const;


};

#endif // MNUMBER_H
