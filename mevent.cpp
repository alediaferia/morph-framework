#include "mevent.h"

#include "mevent_p.h"

MEvent::MEvent(MEvent::Type type) :
    d(new MEventPrivate(this))
{
    d->type = type;
}

MEvent::~MEvent()
{}

MEvent::Type MEvent::type() const
{
    return d->type;
}
