#ifndef MPROPERTY_H
#define MPROPERTY_H

#include "mvariable.h"

// prototypes

template<typename T>
struct is_ptr { static const bool value = false; };

template<typename T>
struct is_ptr<T*> { static const bool value = true; };

template <typename T> class MProperty;
template<typename T, typename C> class MPropertyCSG;

/////


// implementations
class BaseProperty {
public:
    virtual MVariable& operator=(const MVariable& copy) = 0;

    virtual void setValue(const MVariable &v) = 0;
    virtual MVariable value() const = 0;

    BaseProperty* ptr()
    {
        return this;
    }
};


template <typename T>
class MProperty : public BaseProperty {
public:
    MProperty()
    {
        if (is_ptr<T>::value) {
            _value = (T)0;
        }
    }

    virtual ~MProperty()
    {
    }

    virtual void setValue(const MVariable &v)
    {
        _variableProxy = v;
        _value = v.value<T>();
    }

    virtual MVariable value() const
    {
        return _value;
    }

    virtual T& operator=(const T& source)
    {
        _value = source; 
        return _value;
    }
    
    virtual T operator->()
    {
        return _value;
    }
    
    virtual T* operator&()
    {
        return &_value;
    }
    
    virtual operator T const &()
    {
        return _value;
    }
    
    /*virtual T operator++(int)
    {
        _value++;
        return _value;
    }
    
    virtual T operator--(int)
    {
        _value--;
        return _value;
    }*/

    virtual MVariable& operator=(const MVariable& variable)
    {
        _value = variable.value<T>();
        _variableProxy = MVariable(T());
        return _variableProxy;
    }

private:
    MVariable _variableProxy;

protected:
    T _value;
};


template <typename T, typename C>
class MPropertyCSG : public MProperty<T> {
    typedef void (C::*ConstSetter)(const T&);
    typedef void (C::*Setter)(T);
    typedef T (C::*ConstGetter)() const;
    typedef T (C::*Getter)();

public:
    MPropertyCSG(Setter s, Getter g, C* container) :
    _s(s),
    _g(g),
    _cs(0),
    _cg(0),
    _c(container)
    {}
    
    MPropertyCSG(ConstSetter s, ConstGetter g, C* container) :
    _s(0),
    _g(0),
    _cs(s),
    _cg(g),
    _c(container)
    {}
    
    MPropertyCSG(ConstSetter s, Getter g, C* container) :
    _s(0),
    _g(g),
    _cs(s),
    _cg(0),
    _c(container)
    {}
    
    MPropertyCSG(Setter s, ConstGetter g, C* container) :
    _s(s),
    _g(0),
    _cs(0),
    _cg(g),
    _c(container)
    {}
    
    T& operator=(const T& source)
    {
        MProperty<T>::operator=(source);
        
        if (_s) {
            (_c->*_s)(source);
        } else if (_cs) {
            (_c->*_cs)(source);
        }
        
        return MProperty<T>::_value;
    }
    
    operator T const &()
    {
        if (_cg) {
            return (_c->*_cg)();
        }
        
        return (_c->*_g)();
    }
    
private:
    void _set_container(C* c)
    { _c = c; }
    
    void _set_setter(Setter s)
    { _s = s; }
    
    void _set_getter(Getter g)
    { _g = g; }
    
    void _set_setter(ConstSetter s)
    { _cs = s; }
    
    void _set_getter(ConstGetter g)
    { _cg = g; }


private:
    Setter _s;
    Getter _g;
    ConstSetter _cs;
    ConstGetter _cg;
    C *_c;
};

/////


#endif // Morph Property
