#ifndef MOBJECT_H
#define MOBJECT_H

#include "mproperty_p.h"
#include "mshareddataptr.h"
#include "mobject_macros.h"
#include "mobject_p.h"

class MObjectDelegate;
class PropertyContainer;
class MObject;

class MEvent;

/**
 * @class MObject is the base class
 * for most of the Morph API.
 * Making a class inherit from MObject adds
 * a few features to the class.
 * Every class inheriting from MObject is enabled
 * to be used with the generic type mref
 * which makes dynamically allocated object to be
 * automatically destroyed when no more referenced
 * from anywhere. In addition to this, the specific
 * class ClassName::MRef is added automatically to the class
 * when using the M_OBJECT macro in the class definition.
 */
class MObject {

public:
    M_OBJECT_PRIVATE

    M_PROPERTY(const char*, id)
    M_PROPERTY(int, number)

    MObject(MObject *parent = 0);
    virtual ~MObject();

    virtual bool copyable() const;

    virtual bool processEvent(MEvent *event);

private:
    class Private;
    Private* const d;
};

typedef MObject::MRef mref;

#endif
