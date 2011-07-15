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
    M_PROPERTY(int, number)

    MObject(MObject *parent = 0);
    ~MObject();
    
    M_DECLARE_SLOT(testSlot);
    
    template<typename T>
    void registerProperty(int index, void* prop);

    void connect(const char *signal, AbstractSlot *slot)
    {
        m_signals[signal] = slot;
    }

    M_SIGNAL(clicked)

    void setPropertyValue(int index, const MVariable &v);
    MVariable getPropertyValue(int index) const;

protected:
    virtual void propertiesRegistration();

private:
    class Private;
    Private* const d;
};

template<typename T>
void MObject::registerProperty(int index, void* prop)
{
     //m_propsMap.insert(std::pair<int, void* >(index, prop));
}

class MObjectDelegate {
public:
    virtual void destroyed(MObject *) = 0;
};


#endif
