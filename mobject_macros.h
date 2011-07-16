#ifndef MOBJECT_MACROS_H
#define MOBJECT_MACROS_H

// public utility macros

#include <vector>
#include <utility>

class AbstractSlot {
public:
    virtual void invoke() = 0;
};

template<typename C, typename T>
class Slot : public AbstractSlot {
public:
    Slot(C* o, T f, const char *name) :
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

#endif // MOBJECT_MACROS_H
