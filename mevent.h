#ifndef MEVENT_H
#define MEVENT_H

#include "mobject.h"

class MEvent : public MObject
{
    M_OBJECT(MEvent)
public:
    enum Type {
        UndefinedEvent,
        ApplicationStartedEvent,
        ApplicationAboutToQuit,
        SocketDataReadyEvent,
        SocketConnectedEvent,
        RemoteRequestEvent,
        PropertyChangeEvent,
        TimerEvent,
        User = 1500
    };

    MEvent();
    MEvent(Type);
    virtual ~MEvent();

    static MEvent::MRef alloc(Type);

    Type type() const;
    void setType(Type);

private:
    class MEventPrivate;
    MEventPrivate *d;
};

#endif // MEVENT_H
