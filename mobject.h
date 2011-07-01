#ifndef MOBJECT_H
#define MOBJECT_H

#include <map>
#include <list>

#include "mproperty_p.h"
#include <iostream>

#include "mobject_macros.h"

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

    M_DECLARE_SLOT1(setNumber,int)
    M_DECLARE_SLOT(testSlot)
    
    template<typename T>
    void setProperty(int key, const T &t);
    
    template<typename T>
    void registerProperty(int index, void* prop);

private:        
    int m_number;
    std::map<int, void*> m_propsMap;
    std::map<const char*, std::list<slot> > m_slots;
};

template<typename T>
void MObject::setProperty(int key, const T& t)

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
void MObject::registerProperty(int index, void* prop)
{
     m_propsMap.insert(std::pair<int, void* >(index, prop));
}

class MObjectDelegate {
public:
    virtual void destroyed(MObject *) = 0;
};


#endif
