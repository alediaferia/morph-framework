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
    sockaddr incomingAddress;
    int clientSocket;

protected:
    void run()
    {
        while (1) {
           socklen_t size = sizeof(incomingAddress);
           accept(sockd, &incomingAddress, &size);
           server->clientConnected(clientSocket, incomingAddress);

           sleep(1);
        }
    }
};

class MServerSocket::MServerSocketPrivate
{
public:
    MServerSocketPrivate(MServerSocket *m)
        : m(m),
          acceptThread(0)
    {
        memset(&address, 0, sizeof(address));
    }

    ~MServerSocketPrivate()
    {
        delete acceptThread;
    }

    MServerSocket *m;
    MList<mref> listeners;
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
    d->listeners.append(listener);
}

void MServerSocket::start()
{
    d->sockd = socket(AF_INET, SOCK_STREAM, 0);
    d->address.sin_family = AF_INET;
    d->address.sin_addr.s_addr = inet_addr(ip.value().toString().data());
    d->address.sin_port = htons(port);

    bind(d->sockd, (const sockaddr*)&d->address, sizeof(d->address));

    listen(d->sockd, 10);

    d->acceptThread = new AcceptThread(d->sockd, this);
    d->acceptThread->start();

    std::cout << "server started" << std::endl;

}

void MServerSocket::clientConnected(int clientSockD, sockaddr incomingAddress)
{
    MList<mref>::ConstIterator it = d->listeners.constBegin();
    for (; it != d->listeners.constEnd(); ++it) {
        MEventLoop::globalEventLoop()->sendEvent(it.value(),new MEvent(MEvent::SocketConnectedEvent));
    }
}

MString MServerSocket::read(int size)
{}

int MServerSocket::write(const MString &)
{}
