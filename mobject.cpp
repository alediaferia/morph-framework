#include "mobject.h"
#include "mstring.h"

#include "mobjectwatcher.h"
#include "mevent.h"
#include "meventloop.h"
#include "massociativearray.h"

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
        MList<InvokableMethod*> invokablesList = invokables.values();
        MList<InvokableMethod*>::ConstIterator it = invokablesList.constBegin();
        for (; it != invokablesList.constEnd(); ++it) {
            delete it.value();
        }
    }

    MObject *m;
    MAssociativeArray<const char*, InvokableMethod*> invokables;
};

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

bool MObject::copyable() const
{
    static const bool copyable = false;
    return copyable;
}

bool MObject::processEvent(MEvent *event)
{
    mPrint("Trmon!");

    return false;
}

void MObject::registerInvokable(InvokableMethod *invokable, const char *name)
{
    d->invokables[name] = invokable;
}

InvokableMethod* MObject::invokableByName(const char *name)
{
    if (!d->invokables.hasKey(name)) {
        return 0;
    }

    return d->invokables.value(name);
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
