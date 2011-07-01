#ifndef MOBJECT_H
#define MOBJECT_H

#include <map>

#include "mproperty_p.h"
#include <iostream>

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
    };

class MObjectDelegate;
class PropertyContainer;

/**
 * @class MObject is the base class
 * for most of the Morph API. The main advantages
 * of classes inheriting from this
 * are property capable objects and...
 */
class MObject {

public:    
    M_OBJECT(MObject)
    M_PROPERTY(MObjectDelegate*, delegate)
    M_PROPERTY(const char*, id)
    M_COMPLEX_PROPERTY(int, number, MObject)

    MObject(MObject *parent = 0);
    ~MObject();
    
    int getNumber() const;
    void setNumber(int);
    
    template<typename T>
    void invoke(int key, const T &t)
    {
        std::map<int, void*>::iterator it = m_propsMap.find(key);
        if (it == m_propsMap.end()) {
            std::cout << "unable to find property with key " << key << std::endl;
            return;
        }
    
        MProperty<T> MObject::*prop = it->second;
        std::cout << "setting value for property " << prop << std::endl;
        ((*this).*prop)(t);
    }
    
    template<typename T>
    void registerProperty(int index, void* prop)
    {
         m_propsMap.insert(std::pair<int, void* >(index, prop));
    }

private:        
    int m_number;
    std::map<int, void*> m_propsMap;
};

class MObjectDelegate {
public:
    virtual void destroyed(MObject *) = 0;
};


#endif
