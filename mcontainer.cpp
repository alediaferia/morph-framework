#include "mcontainer.h"

class MContainer::MContainerPrivate
{
public:
    MContainerPrivate(MContainer *m) :
        m(m),
        data(0),
        size(0)
    {}

    ~MContainerPrivate()
    {
        free(data);
    }

    MContainer *m;
    void *data;
    int size;
};

MContainer::MContainer() : MObject(),
    d(new MContainerPrivate(this))
{
}

MContainer::~MContainer()
{
    delete d;
}

void MContainer::setData(void *data, int length)
{
    free(d->data);
    d->data = malloc(length);
    memcpy(d->data, data, length);
    d->size = length;
}

void* MContainer::data() const
{
    return d->data;
}

int MContainer::size() const
{
    return d->size;
}
