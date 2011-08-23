#include "mevent.h"

#include "mevent_p.h"

MEvent::MEvent(MEvent::Type type) : MObject(),
    d(new MEventPrivate(this))
{
    d->type = type;
}

MEvent::MEvent() : MObject(),
    d(new MEventPrivate(this))
{}

MEvent::~MEvent()
{}

MEvent::MRef MEvent::alloc(Type t)
{
    return MEvent::MRef(new MEvent(t));
}

MEvent::Type MEvent::type() const
{
    return d->type;
}

void MEvent::setType(Type t)
{
    d->type = t;
}
