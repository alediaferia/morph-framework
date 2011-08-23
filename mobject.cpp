#include "mobject.h"
#include "mstring.h"

#include "mobjectwatcher.h"
#include "mevent.h"
#include "meventloop.h"
#include "massociativearray.h"
#include "minvokablemethod.h"
#include "mcontainer.h"

#include <map>
#include <string>
#include "mutils.h"

// TODO: use a faster container for
//       invokables and add automated
//       iterating-deletion functions for containers

class MObject::MObjectPrivate {
public:
    MObjectPrivate(MObject *m) :
        m(m)
    {}

    ~MObjectPrivate()
    {
    }

    MObject *m;
    std::map<std::string, mref> invokables;
};

// MObject::MRef

MObject::MRef::MRef(MObject* object) :  MSharedPtr<MObject>(object)
{}

MObject::MRef::MRef(const MRef &ref) : MSharedPtr<MObject>(ref)
{}

MObject::MRef::~MRef()
{}

MObject* MObject::MRef::operator->() const
{
    return MSharedPtr<MObject>::operator->();
}

MObject* MObject::MRef::data() const
{
    return MSharedPtr<MObject>::data();
}

bool MObject::MRef::operator==(const MObject::MRef &o) const
{
    return data()->equals(o);
}

bool MObject::MRef::isNull() const
{
    return data() == 0;
}

// end of MObject::MRef

std::ostream& operator<<(std::ostream &stream, MObject::MRef o)
{
    MString::MRef stringRep = o->toString();
    return stream << stringRep << std::endl;
}

MObject::MObject() :
    d(new MObjectPrivate(this))
{
    //std::cout << "created object" << std::endl;
}

MObject::~MObject()
{
    //std::cout << "destroyed object" << std::endl;
    delete d;
}

bool MObject::processEvent(MObject::MRef event)
{
    return false;
}

void MObject::registerInvokable(MInvokableMethod* invokable, const char *name)
{
    // invokables cannot be overwritten
    std::string key(name);
    if (d->invokables.count(key) != 0) {
        return;
    }
    MContainer::MRef invokablePtr = MContainer::alloc();
    invokablePtr->setData(&invokable, sizeof(MInvokableMethod*));
    d->invokables[key] = invokablePtr;
}

MInvokableMethod* MObject::invokableByName(const char *name)
{
    std::string nameKey(name);
    if (d->invokables.count(nameKey) == 0) {
        return 0;
    }

    MContainer::MRef invokablePtr = d->invokables[nameKey];
    return *(MInvokableMethod**)invokablePtr->data();
}

MObject::MRef MObject::alloc()
{
    return MObject::MRef(new MObject);
}

bool MObject::equals(const MObject::MRef &o) const
{
    return this == o.data();
}

MObject::MRef MObject::toString() const
{
    int classNameLength = strlen(this->className());
    static const char instanceOf[] = " instance of ";
    char *stringRep = new char[classNameLength + strlen(instanceOf) + 18];
    sprintf(stringRep, "0x%lx%s%s", reinterpret_cast<unsigned long>(this), instanceOf, this->className());

    mref string = MString::alloc(stringRep);
    delete[] stringRep;

    return string;
}
