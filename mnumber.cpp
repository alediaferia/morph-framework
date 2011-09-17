#include "mnumber.h"
#include "mstring.h"

class MNumber::MNumberPrivate
{
public:
    MNumberPrivate(MNumber *m) :
        m(m),
        value(0)
    {}

    MNumberPrivate(const MNumberPrivate& copy) :
        m(copy.m),
        value(copy.value)
    {}

    MNumber *m;
    long double value;
};

MNumber::MNumber() : MObject()
{
}

MNumber::~MNumber()
{
    delete d;
}

MNumber::MRef MNumber::init()
{
    d = new MNumber::MNumberPrivate(this);
    return _self;
}

MNumber::MRef MNumber::init(double value)
{
    init();
    setDoubleValue(value);
    return _self;
}

MNumber::MRef MNumber::init(float value)
{
    init();
    setFloatValue(value);
    return _self;
}

MNumber::MRef MNumber::init(int value)
{
    init();
    setIntValue(value);
    return _self;
}

MNumber::MRef MNumber::init(long double value)
{
    init();
    setLongDoubleValue(value);
    return _self;
}

MNumber::MRef MNumber::init(long long value)
{
    init();
    setLongLongValue(value);
    return _self;
}

MNumber::MRef MNumber::init(long value)
{
    init();
    setLongValue(value);
    return _self;
}

MNumber::MRef MNumber::init(unsigned int value)
{
    init();
    setUnsignedIntValue(value);
    return _self;
}

MNumber::MRef MNumber::init(unsigned long long value)
{
    init();
    setUnsignedLongLongValue(value);
    return _self;
}

MNumber::MRef MNumber::init(unsigned long value)
{
    init();
    setUnsignedLongValue(value);
    return _self;
}

void MNumber::setDoubleValue(double value)
{
    d->value = value;
}

void MNumber::setFloatValue(float value)
{
    d->value = value;
}

void MNumber::setIntValue(int value)
{
    d->value = value;
}

void MNumber::setLongDoubleValue(long double value)
{
    d->value = value;
}

void MNumber::setLongLongValue(long long value)
{
    d->value = value;
}

void MNumber::setLongValue(long value)
{
    d->value = value;
}

void MNumber::setUnsignedIntValue(unsigned int value)
{
    d->value = value;
}

void MNumber::setUnsignedLongLongValue(unsigned long long value)
{
    d->value = value;
}

void MNumber::setUnsignedLongValue(unsigned long value)
{
    d->value = value;
}

double MNumber::doubleValue() const
{
    return d->value;
}

float MNumber::floatValue() const
{
    return d->value;
}

int MNumber::intValue() const
{
    return d->value;
}

long double MNumber::longDoubleValue() const
{
    return d->value;
}

long long MNumber::longLongValue() const
{
    return d->value;
}

long MNumber::longValue() const
{
    return d->value;
}

unsigned int MNumber::unsignedIntValue() const
{
    return d->value;
}

unsigned long long MNumber::unsignedLongLongValue() const
{
    return d->value;
}

unsigned long MNumber::unsignedLongValue() const
{
    return d->value;
}

mref MNumber::toString() const
{
    int digitCount = 0;
    int v = d->value;
    while (v > 0) {
        v = v / 10;
        digitCount++;
    }

    // not working: cast by correct type
    char *str = new char[digitCount + 1];
    sprintf(str, "%d", d->value);
    MString::MRef string = MString::alloc()->init(str);
    delete[] str;

    return string;
}

mref MNumber::copy() const
{
    return MNumber::alloc()->init(_self->d->value);
}
