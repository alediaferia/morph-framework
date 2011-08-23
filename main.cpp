#include "mstring.h"
#include "mlist.h"
#include "meventloop.h"
#include "mserversocket.h"

class ConnectionController : public MObject
{
    M_OBJECT(ConnectionController)
public:
    ConnectionController()
    {
        registerInvokable(M_INVOKABLE1(ConnectionController, clientConnected));
    }

    M_INVOKABLE void clientConnected(mref clientSocket)
    {
        m_socketRef = clientSocket;
    }

private:
    mref m_socketRef;
};

int main(int argc, char **argv)
{
    MEventLoop eLoop;
    MServerSocket::MRef server = MServerSocket::alloc();
    server->setAddress(MString::alloc("127.0.0.1"));
    server->setPort(3000);

    mref connectionController = ConnectionController::alloc();
    server->addConnectionListener(connectionController);

    server->start();

    eLoop.run();
}
