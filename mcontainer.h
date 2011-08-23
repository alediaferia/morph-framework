#ifndef MCONTAINER_H
#define MCONTAINER_H

#include "mobject.h"

class MContainer : public MObject
{
    M_OBJECT(MContainer)
public:
    MContainer();
    ~MContainer();

    void setData(void *data, int length);
    void* data() const;
    int size() const;

private:
    class MContainerPrivate;
    MContainerPrivate *d;
};

#endif // MCONTAINER_H
