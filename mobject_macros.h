#ifndef MOBJECT_MACROS_H
#define MOBJECT_MACROS_H

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
    M_RUNTIME_FACILITIES(_name) \
    M_ALLOCABLE(_name) \

#define M_UNALLOCABLE_OBJECT(_name) \
    M_RUNTIME_FACILITIES(_name)

#define M_RUNTIME_FACILITIES(_name) \
    public:\
    M_DEFINE_INVOKABLES(_name) \
    class MRef : public MObject::MRef \
    { \
    public: \
        MRef(_name* object = 0) : MObject::MRef((MObject*)object), \
            m_object(object) \
        {} \
        MRef(const MObject::MRef &copy) : MObject::MRef(copy), \
            m_object((_name*)copy.data()) \
        {} \
        _name* operator->() const \
        { \
            return m_object; \
        } \
        _name* data() const \
        { \
            return m_object; \
        } \
    private:\
        _name* m_object;\
    }; \
    virtual const char* className() const { \
        static const char _className[] = #_name; \
        return _className; \
    } \

#define M_ALLOCABLE(_name) \
    static _name::MRef alloc() \
    { \
        return _name::MRef(new _name()); \
    } \

#define M_DEFINE_INVOKABLES(_name) \
    typedef void (_name::*M0ArgFunc)(); \
    typedef InvokableMethod0<_name,M0ArgFunc> MInvokable0; \
    typedef void (_name::*M1ArgFunc)(mref); \
    typedef InvokableMethod1<_name,M1ArgFunc> MInvokable1;

#define M_INVOKABLE0(classname, name) \
    new MInvokable0(this, &classname::name), #name

#define M_INVOKABLE1(classname, name) \
    new MInvokable1(this, &classname::name), #name

#define M_INVOKABLE2(classname, name) \
    new MInvokable2(this, &classname::name), #name

#define M_INVOKABLE

#define M_UNUSED(var) (void)(var);

#endif // MOBJECT_MACROS_H
