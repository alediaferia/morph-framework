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
    std::map<int, BaseProperty*> m_props;
};


#define M_DELEGATE_FUNC(dname, func) \
if (this->dname) { \
    this->dname->func; \
}

MObject::MObject(MObject *parent) :
    d(new Private(this)),
    M_SYNTHETIZE_PROPERTY(delegate),
    M_SYNTHETIZE_PROPERTY(id),
    M_SYNTHETIZE_PROPERTY(number),
    M_REGISTER_SLOT(MObject, testSlot)
{
    std::cout << "registering object to watcher " << this << std::endl;
    MObjectWatcher::instance()->registerObject(this);

    propertiesRegistration();
}

MObject::~MObject()
{
    delete d;
    M_DELEGATE_FUNC(delegate, destroyed(this))
    MObjectWatcher::instance()->objectDeleted(this);
}

void MObject::propertiesRegistration()
{
    d->m_props.insert(std::pair<int, BaseProperty*>(0, number.ptr()));
}

void MObject::setPropertyValue(int index, const MVariable &v)
{
    BaseProperty *prop = d->m_props[index];
    prop->setValue(v);
}

MVariable MObject::getPropertyValue(int index) const
{
    return d->m_props[index]->value();
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

void MObject::testSlot()
{
    std::cout << "test slot" << std::endl;
}

