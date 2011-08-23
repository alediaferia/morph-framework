#ifndef MOBJECT_H
#define MOBJECT_H

#include "mproperty_p.h"
#include "msharedptr.h"
#include "mobject_macros.h"
#include "mobject_p.h"

class PropertyContainer;
class MInvokableMethod;

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

   // M_PROPERTY(const char*, id)
   // M_PROPERTY(int, number)

    class MRef;

    MObject();
    virtual ~MObject();

    virtual bool processEvent(MObject::MRef event);
    virtual bool equals(const MObject::MRef &) const;

    MInvokableMethod* invokableByName(const char *name);

    virtual MObject::MRef toString() const;
    static MObject::MRef alloc();

protected:
    void registerInvokable(MInvokableMethod*, const char *name);

private:
    class MObjectPrivate;
    MObjectPrivate* d;
};

class MObject::MRef : public MSharedPtr<MObject> {
public:
    MRef(MObject* object = 0);
    MRef(const MRef &ref);
    virtual ~MRef();
    virtual MObject* operator->() const;
    virtual MObject* data() const;
    virtual bool operator==(const MObject::MRef &object) const;
    bool isNull() const;
};

std::ostream& operator<<(std::ostream&, MObject::MRef);

#include "minvokablemethod.h"
#include "morph_defines.h"

#endif
