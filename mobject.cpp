#include "mobject.h"
#include "mstring.h"

#include "mobjectwatcher.h"
#include "mevent.h"
#include "meventloop.h"

#include "mutils.h"

class MObject::Private {
public:
    Private(MObject *m) :
        m(m)
    {}

    MObject *m;
};

MObject::MObject(MObject *parent) :
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
