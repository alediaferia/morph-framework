#include "mserversocket.h"
#include "mlist.h"
#include "mthread.h"
#include "meventloop.h"
#include "mevent.h"

class AcceptThread : public MThread
{
public:
    AcceptThread(int sockd, MServerSocket* server) : MThread(),
        sockd(sockd),
        server(server)
    {}

private:
    int sockd;
    MServerSocket *server;

protected:
    void run()
    {
        while (1) {
           struct sockaddr_in incomingAddress;
           socklen_t size = sizeof(incomingAddress);
           int clientSocket = accept(sockd, (struct sockaddr*)&incomingAddress, &size);
           server->clientConnected(clientSocket, incomingAddress);
        }
    }
};

class MServerSocket::MServerSocketPrivate
{
public:
    MServerSocketPrivate(MServerSocket *m)
        : m(m),
          listeners(MList::alloc()),
          acceptThread(0)
    {
        memset(&address, 0, sizeof(address));
    }

    ~MServerSocketPrivate()
    {
        delete acceptThread;
    }

    MServerSocket *m;
    MList::MRef listeners;
    int sockd;
    sockaddr_in address;
    AcceptThread *acceptThread;
};

MServerSocket::MServerSocket() : MSocket(),
    d(new MServerSocketPrivate(this))
{

}

MServerSocket::~MServerSocket()
{
    delete d;
}

void MServerSocket::addConnectionListener(mref listener)
{
    d->listeners->append(listener);
}

void MServerSocket::start()
{
    d->sockd = socket(AF_INET, SOCK_STREAM, 0);
    d->address.sin_family = AF_INET;
    d->address.sin_addr.s_addr = inet_addr(address()->data());
    d->address.sin_port = htons(port());

    bind(d->sockd, (const sockaddr*)&d->address, sizeof(d->address));

    listen(d->sockd, 10);

    d->acceptThread = new AcceptThread(d->sockd, this);
    d->acceptThread->start();

    std::cout << "server started" << std::endl;
}

void MServerSocket::clientConnected(int clientSockD, sockaddr_in incomingAddress)
{
    MSocket::MRef clientSocket = MSocket::alloc();
    clientSocket->setDescriptor(clientSockD);
    clientSocket->setPort(ntohs(incomingAddress.sin_port));
    clientSocket->setAddress(MString::alloc(inet_ntoa(incomingAddress.sin_addr)));

    MList::ConstIterator it = d->listeners->constBegin();
    for (; it != d->listeners->constEnd(); ++it) {
        mref listener = it.value();
        MInvokableMethod* method = listener->invokableByName("clientConnected");
        if (!method) {
            continue;
        }
        method->invoke(clientSocket);
    }
}
