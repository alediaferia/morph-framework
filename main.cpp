#include <iostream>
#include "mlist.h"
#include "mstring.h"
#include "mobject.h"

#include "mthread.h"
#include "mutils.h"
#include "mpair.h"
#include "meventloop.h"
#include "massociativearray.h"
#include "mevent.h"
#include "mserversocket.h"

class Listener : public MObject
{
public:
    M_OBJECT(Listener)
    Listener()
    {}

    bool processEvent(MEvent *event) {
        if (event->type() == MEvent::SocketConnectedEvent) {
            mPrint("Someone connected!!");
        }
        return true;
    }
};

class ServerInitializer : public MObject
{
public:
    M_OBJECT(ServerInitializer)
    ServerInitializer(mref listener) :
        m_listener(listener)
    {}

    bool processEvent(MEvent *event)
    {
        if (event->type() == MEvent::ApplicationStartedEvent) {
            m_server.ip = MString("172.20.10.4");
            m_server.port = 3400;

            m_server.addConnectionListener(m_listener);
            m_server.start();
        }

        return true;
    }

private:
    MServerSocket m_server;
    mref m_listener;
};

int main(int argc, char **argv)
{

    mref listener = new Listener;
    mref initializer = new ServerInitializer(listener);

    MEventLoop *mainLoop = MEventLoop::globalEventLoop();
    MEvent startEvent(MEvent::ApplicationStartedEvent);
    mainLoop->sendEvent(initializer, &startEvent);

    mainLoop->run();

    return 0;
}
