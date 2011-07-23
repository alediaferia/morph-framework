#include "mevent.h"

#include "mevent_p.h"

MEvent::MEvent() :
    d(new MEventPrivate(this))
{
}

MEvent::~MEvent()
{}

MEvent::Type MEvent::type() const
{
    return d->type;
}
