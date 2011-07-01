#ifndef MOBJECT_MACROS_H
#define MOBJECT_MACROS_H

// public utility macros

#define M_PROPERTY(type, name) \
    public: \
    MProperty<type> name;

#define M_SYNTHETIZE_PROPERTY(name) name()

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
    typedef void (_name::*slot)(); \
    typedef void (_name::*slot1)(void*); \
    typedef void (_name::*slot2)(void*, void*);

#define M_DECLARE_SLOT(_name) \
    void _name(); \
    slot _name##_slot;

#define M_DECLARE_SLOT1(_name, arg) \
    void _name(arg); \
    slot1 _name##_slot;

#define M_REGISTER_SLOT(_class, _name) \
    _name##_slot(&_class::_name)

#define M_REGISTER_SLOT1(_class, _name) \
    _name##_slot(reinterpret_cast< _class::slot1 >(&_class::_name))

#define M_INVOKE_SLOT(object, name) \
    (object->*(object->name##_slot))()

#define M_INVOKE_SLOT1(object, name, arg) \
    (object->*(object->name##_slot))((void*)arg)

#define M_SIGNAL(_name) \
    void _name() { \
        std::list<slot> _slots = m_slots[_name]; \
        for (int i = 0; i < _slots.size(); i++) { \
            (this->*(_slots[i]))(); \
        } \
    }

#endif // MOBJECT_MACROS_H
