#ifndef MOBJECT_MACROS_H
#define MOBJECT_MACROS_H

// public utility macros and classes

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
// method f of type T is invoked on object o of type C
template<typename C, typename T>
class InvokableMethod0 : public InvokableMethod {
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
class InvokableMethod1 : public InvokableMethod {
public:
    InvokableMethod1(C* o, T f) :
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
    InvokableMethod2(C* o, T f) :
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
    M_DEFINE_INVOKABLES(_name) \
    class MRef : public MObject::MRef \
    { \
    public: \
        MRef(_name* object) : \
            MObject::MRef(object) \
        {} \
        virtual _name* operator->() const \
        { \
            return (_name*)MObject::MRef::operator ->(); \
        } \
    private:\
        _name* m_object;\
    }; \
    virtual const char* className() const { \
        static const char _className[] = #_name; \
        return _className; \
    } \

#define M_DEFINE_INVOKABLES(_name) \
    typedef void (_name::*M0ArgFunc)(); \
    typedef InvokableMethod0<_name,M0ArgFunc> MInvokable0;

#define M_REGISTER_INVOKABLE0(classname, name) \
    registerInvokable(new MInvokable0(this, &classname::name), #name);

#define M_UNUSED(var) (void*)(var);

#endif // MOBJECT_MACROS_H
