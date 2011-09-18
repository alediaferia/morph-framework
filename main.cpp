#include "mstring.h"
#include "mlist.h"
#include "meventloop.h"
#include "mserversocket.h"
#include "mnumber.h"

class ConnectionController : public MObject
{
    M_OBJECT(ConnectionController)
public:
    ConnectionController()
    {
        registerInvokable(M_INVOKABLE1(ConnectionController, clientConnected));
        registerInvokable(M_INVOKABLE1(ConnectionController, readyRead));
    }

    M_INVOKABLE void clientConnected(mref clientSocket)
    {
        m_socketRef = clientSocket;
        m_socketRef->addReadyReadListener(_self);
        m_socketRef->waitForReadyRead(false);
        std::cout << "waiting for bytes ready" << std::endl;
    }

    M_INVOKABLE void readyRead(mref bytes)
    {
        std::cout << "ready to read " << ((MNumber::MRef)bytes)->intValue() << std::endl;
    }

private:
    MSocket::MRef m_socketRef;
};

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
    std::cout << MString::alloc()->init("Antonio e ale") << std::endl;
}
