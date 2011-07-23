#ifndef MOBJECT_H
#define MOBJECT_H

#include "mproperty_p.h"
#include "mshareddataptr.h"
#include "mobject_macros.h"

class MObjectDelegate;
class PropertyContainer;

class MObject;
typedef MSharedPtr<MObject> mref;

/**
 * @class MObject is the base class
 * for most of the Morph API. The main advantages
 * of classes inheriting from this
 * are property capable objects and...
 */
class MObject {

public:    
    M_OBJECT(MObject)
    M_PROPERTY(const char*, id)
    M_PROPERTY(int, number)

    MObject(MObject *parent = 0);
    ~MObject();

    virtual bool copyable() const;

private:
    class Private;
    Private* const d;
};


#endif
