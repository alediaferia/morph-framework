#include "mobject.h"
#include "mstring.h"

#include "mobjectwatcher.h"
#include "mevent.h"
#include "meventloop.h"
#include "massociativearray.h"
#include "minvokablemethod.h"

#include "mutils.h"

// TODO: use a faster container for
//       invokables and add automated
//       iterating-deletion functions for containers

class MObject::Private {
public:
    Private(MObject *m) :
        m(m)
    {}

    ~Private()
    {
        MList<MInvokableMethod*> invokablesList = invokables.values();
        MList<MInvokableMethod*>::ConstIterator it = invokablesList.constBegin();
        for (; it != invokablesList.constEnd(); ++it) {
            delete it.value();
        }
    }

    MObject *m;
    MAssociativeArray<const char*, MInvokableMethod*> invokables;
};

// MObject::MRef

MObject::MRef::MRef(MObject* object) :  MSharedPtr<MObject>(object)
{}

MObject::MRef::~MRef()
{}

MObject* MObject::MRef::operator->() const
{
    return MSharedPtr<MObject>::operator->();
}

// end of MObject::MRef

MObject::MObject() :
    d(new Private(this)),
    M_SYNTHETIZE_PROPERTY(id),
    M_SYNTHETIZE_PROPERTY(number)
{
}

MObject::~MObject()
{
    //printf("Object %ld dying\n", (size_t)this);

    delete d;
}

bool MObject::processEvent(MEvent *event)
{
    mPrint("Trmon!");

    return false;
}

void MObject::registerInvokable(MInvokableMethod *invokable, const char *name)
{
    // invokables cannot be overwritten
    if (d->invokables.hasKey(name)) {
        return;
    }
    d->invokables[name] = invokable;
}

MInvokableMethod* MObject::invokableByName(const char *name)
{
    if (!d->invokables.hasKey(name)) {
        return 0;
    }

    return d->invokables.value(name);
}

MObject::MRef MObject::alloc()
{
    return MObject::MRef(new MObject);
}

/*void MObject::setNumber(int n)
{
    std::cout << "custom setter for number " << std::endl;
    m_number = n;
}

int MObject::getNumber() const
{
    std::cout << "custom getter for number " << std::endl;
    return m_number;
}
*/
