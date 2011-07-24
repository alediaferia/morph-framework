#ifndef MOBJECT_MACROS_H
#define MOBJECT_MACROS_H

// public utility macros

#include <vector>
#include <utility>

class InvokableMethod {
public:
    virtual void invoke()
    {}
    virtual void invoke(void *arg1)
    {}
    virtual void invoke(void *arg1, void* arg2)
    {}
};

// class that identifies a generic
// invokable method that takes
// no arguments
// method f of type T is invoked on object of type C
template<typename C, typename T>
class InvokableMethod0 : public InvokableMethod {
public:
    InvokableMethod0(C* o, T f, const char *name) :
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
class InvokableMethod1 : public InvokableMethod {
public:
    InvokableMethod1(C* o, T f, const char *name) :
        o(o),
        f(f)
    {
    }

    void invoke(void *arg1)
    {
        (o->*f)(arg1);
    }

private:
    C* o;
    T f;
};

template<typename C, typename T>
class InvokableMethod2 : public InvokableMethod {
public:
    InvokableMethod2(C* o, T f, const char *name) :
        o(o),
        f(f)
    {
    }

    void invoke(void *arg1, void* arg2)
    {
        (o->*f)(arg1, arg2);
    }

private:
    C* o;
    T f;
};

#define M_PROPERTY(type, name) \
    public: \
    MProperty<type> name;

#define M_SYNTHETIZE_PROPERTY(p) p()

#define M_COMPLEX_PROPERTY(type, name, _class) \
    public: \
    MPropertyCSG<type, _class> name;

#define M_SYNTHETIZE_COMPLEX_PROPERTY(name, _setter, _getter, _class) \
    name(&_class::_setter,&_class::_getter, this)

#define M_OBJECT(_name) \
    template <typename X> \
    struct PropTypeHelper { \
        typedef MProperty<X> _name::*typed_prop_member; \
    }; \
    virtual const char* className() const { \
        static const char _className[] = #_name; \
        return _className; \
    } \
    typedef MSharedPtr<_name> mref;

#endif // MOBJECT_MACROS_H
