#ifndef MEVENT_H
#define MEVENT_H

class MEvent
{
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

    MEvent(Type);
    virtual ~MEvent();

    Type type() const;

private:
    class MEventPrivate;
    MEventPrivate * d;
};

#endif // MEVENT_H
