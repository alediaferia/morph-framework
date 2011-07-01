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
    typedef void (_name::*SlotPtr)(); \
    typedef Slot<_name, SlotPtr> ClassSlot; \
    private: \
    std::map<const char*, AbstractSlot*> m_signals;

#define M_SIGNAL(name) \
    void name() { \
        std::map<const char*, AbstractSlot*>::const_iterator it = m_signals.find(#name); \
        if (it != m_signals.end()) { \
            it->second->invoke(); \
        } \
    }

#define M_DECLARE_SLOT(name) \
    void name(); \
    ClassSlot name##_slot;

#define M_REGISTER_SLOT(_class, name) \
    name##_slot(this, &_class::name, #name)

#define M_SLOT(object, name) \
    (AbstractSlot*)&object->name##_slot


#endif // MOBJECT_MACROS_H
