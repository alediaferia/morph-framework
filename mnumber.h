#ifndef MNUMBER_H
#define MNUMBER_H

#include "mobject.h"

class MNumber : public MObject
{
    M_OBJECT(MNumber)
public:
    MNumber();
    ~MNumber();

    MNumber::MRef init();
    MNumber::MRef init(int);
    MNumber::MRef init(unsigned int);
    MNumber::MRef init(long);
    MNumber::MRef init(long long);
    MNumber::MRef init(unsigned long);
    MNumber::MRef init(unsigned long long);
    MNumber::MRef init(float);
    MNumber::MRef init(double);
    MNumber::MRef init(long double);

    void setIntValue(int);
    void setUnsignedIntValue(unsigned int);
    void setLongValue(long);
    void setLongLongValue(long long);
    void setUnsignedLongValue(unsigned long);
    void setUnsignedLongLongValue(unsigned long long);
    void setFloatValue(float);
    void setDoubleValue(double);
    void setLongDoubleValue(long double);

    int intValue() const;
    unsigned int unsignedIntValue() const;
    long longValue() const;
    long long longLongValue() const;
    unsigned long unsignedLongValue() const;
    unsigned long long unsignedLongLongValue() const;
    float floatValue() const;
    double doubleValue() const;
    long double longDoubleValue() const;

    mref toString() const;
    mref copy() const;

private:
    class MNumberPrivate;
    MNumberPrivate *d;
};

#endif // MNUMBER_H
