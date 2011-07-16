#include "mobject.h"

#include <utility>
#include "mstring.h"

#include "mobjectwatcher.h"


class MObject::Private {
public:
    Private(MObject *m) :
        m(m)
    {}

    MObject *m;
};


#define M_DELEGATE_FUNC(dname, func) \
if (this->dname) { \
    this->dname->func; \
}

MObject::MObject(MObject *parent) :
    d(new Private(this)),
    M_SYNTHETIZE_PROPERTY(delegate),
    M_SYNTHETIZE_PROPERTY(id),
    M_SYNTHETIZE_PROPERTY(number)
{
    std::cout << "registering object to watcher " << this << std::endl;
    MObjectWatcher::instance()->registerObject(this);
}

MObject::~MObject()
{
    delete d;
    M_DELEGATE_FUNC(delegate, destroyed(this))
    MObjectWatcher::instance()->objectDeleted(this);
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
