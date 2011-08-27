#include "msocket.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include "mlist.h"

class MSocket::MSocketPrivate
{
public:
    MSocketPrivate(MSocket *m) :
        m(m),
        listeners(MList::alloc())
    {}

    MSocket *m;
    uint16_t port;
    MString::MRef address;
    MList::MRef listeners;

    static void socketThreadFunc(void *data)
    {
        MSocket::MSocketPrivate *dptr = (MSocket::MSocketPrivate*)data;
        dptr->m->waitForReadyRead();
        MList::ConstIterator it = dptr->listeners->constBegin();
        for (; it != dptr->listeners->constEnd(); ++it) {
            mref object = it.value();
            MInvokableMethod *invokable = object->invokableByName("readyRead");
            if (invokable) {

            }
        }
    }
};

MSocket::MSocket() : MIODevice(),
    d(new MSocketPrivate(this))
{}

MSocket::~MSocket()
{
    delete d;
}

void MSocket::setAddress(MString::MRef address)
{
    d->address = address;
}

MString::MRef MSocket::address() const
{
    return d->address;
}

void MSocket::setPort(uint16_t port)
{
    d->port = port;
}

uint16_t MSocket::port() const
{
    return d->port;
}

bool MSocket::connect()
{
    int fd = ::socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    struct sockaddr_in address;
    memset(&address, 0, sizeof(sockaddr_in));

    address.sin_addr.s_addr = inet_addr(d->address->data());
    address.sin_port = htons(d->port);
    address.sin_family = AF_INET;

    if (::connect(fd, (const sockaddr*)&address, sizeof(address)) != 0) {
        return false;
    }

    return true;
}

bool MSocket::waitForReadyRead()
{
    fd_set socks;

    FD_ZERO(&socks);
    FD_SET(descriptor(), &socks);
    int readySocks = select(descriptor() + 1, &socks, 0, 0, 0);

    if (!readySocks) {
        return false;
    }

    if (readySocks < 0) {
        return false;
    }

    if (FD_ISSET(descriptor(), &socks)) {
        return true;
    }

    return false;
}

ssize_t MSocket::availableBytes() const
{
    int available = -1;

    if (ioctl(descriptor(), FIONREAD, &available) < 0) {
        return -1;
    }

    return (ssize_t) available;
}

void MSocket::addReadyReadListener(mref listener)
{
    d->listeners->append(listener);
}
