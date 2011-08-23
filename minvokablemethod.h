#ifndef MINVOKABLEMETHOD_H
#define MINVOKABLEMETHOD_H

#include "morph_defines.h"

/**
 * @class MInvokableMethod
 * This is the base class for every invokable method
 * defined in an MObject or its subclasses.
 * Calling the wrong invoke method (aka the one not related
 * with the current invokable method) causes nothing to happen.
 */
class MInvokableMethod
{
public:
    virtual void invoke();
    virtual void invoke(mref);
    virtual void invoke(mref, mref);
    virtual void invoke(mref, mref, mref);
};

// invokable method that takes
// no arguments
// method f of type T is invoked on object o of type C
template<typename C, typename T>
class InvokableMethod0 : public MInvokableMethod {
public:
    InvokableMethod0(C* o, T f) :
        o(o),
        f(f)
    {
    }
    void invoke()
    {
        (o->*f)();
    }

private:
    C* o;
    T f;
};

template<typename C, typename T>
class InvokableMethod1 : public MInvokableMethod {
public:
    InvokableMethod1(C* o, T f) :
        o(o),
        f(f)
    {
    }

    void invoke(mref arg1)
    {
        (o->*f)(arg1);
    }

private:
    C* o;
    T f;
};

template<typename C, typename T>
class InvokableMethod2 : public MInvokableMethod {
public:
    InvokableMethod2(C* o, T f) :
        o(o),
        f(f)
    {
    }

    void invoke(mref arg1, mref arg2)
    {
        (o->*f)(arg1, arg2);
    }

private:
    C* o;
    T f;
};


#endif // MINVOKABLEMETHOD_H
