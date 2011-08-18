#include "mfile.h"
#include "mobject.h"
#include "mevent.h"
#include "msocket.h"
#include "mserversocket.h"
#include "meventloop.h"

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
        MSocket *socket = (MSocket*)clientSocket.data();
        std::cout << "client with ip " << socket->address() << " connected." << std::endl;
    }
};

int main(int argc, char **argv)
{
    MEventLoop eLoop;
    MServerSocket::MRef server = MServerSocket::alloc();
    server->setAddress("127.0.0.1");
    server->setPort(3000);

    mref connectionController = ConnectionController::alloc();
    server->addConnectionListener(connectionController);

    server->start();

    eLoop.run();
}
