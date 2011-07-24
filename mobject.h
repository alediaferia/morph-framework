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
 * for most of the Morph API. The main advantages
 * of classes inheriting from this
 * are property capable objects and...
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

#endif
