#include "mstring.h"
#include "mlist.h"
#include "meventloop.h"
#include "mserversocket.h"
#include "mnumber.h"

/*class ConnectionController : public MObject
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
        m_socketRef->waitForReadyRead();
        std::cout << "socket ready to read " << m_socketRef->availableBytes() << " bytes." << std::endl;
    }

private:
    MSocket::MRef m_socketRef;
};*/

class Test : public MObject
{
    M_OBJECT(Test)
public:
    Test() : MObject(),
        list(MList::alloc())
    {}

    ~Test()
    {
        std::cout << "Test dying" << std::endl;
    }

    void addSelf()
    {
        list->append(_self);
    }

private:
    MList::MRef list;
};

int main(int argc, char **argv)
{
    /*MEventLoop eLoop;
    MServerSocket::MRef server = MServerSocket::alloc();
    server->setAddress(MString::alloc("127.0.0.1"));
    server->setPort(3000);

    mref connectionController = ConnectionController::alloc();
    server->addConnectionListener(connectionController);

    server->start();

    eLoop.run();*/
}
