#include "mobject.h"
#include "mstring.h"

#include "mobjectwatcher.h"


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
    printf("%ld dying\n", (size_t)this);
    delete d;
}

bool MObject::copyable() const
{
    static const bool copyable = false;
    return copyable;
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
