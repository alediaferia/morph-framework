#ifndef MEVENT_H
#define MEVENT_H

class MEvent
{
public:
    enum Type {
        UndefinedEvent,
        ApplicationStartedEvent,
        SocketDataReadyEvent,
        SocketConnectedEvent,
        RemoteRequestEvent,
        PropertyChangeEvent,
        TimerEvent,
        User = 1500
    };

    MEvent();
    virtual ~MEvent();

    Type type() const;

private:
    class MEventPrivate;
    MEventPrivate const* d;
};

#endif // MEVENT_H
