#include "msocket.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class MSocket::MSocketPrivate
{
public:
    MSocketPrivate(MSocket *m) :
        m(m)
    {}

    MSocket *m;
    uint16_t port;
    MString address;
};

MSocket::MSocket() : MIODevice(),
    d(new MSocketPrivate(this))
{}

MSocket::~MSocket()
{
    delete d;
}

void MSocket::setAddress(const MString &address)
{
    d->address = address;
}

MString MSocket::address() const
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

    address.sin_addr.s_addr = inet_addr(d->address.data());
    address.sin_port = htons(d->port);
    address.sin_family = AF_INET;

    if (::connect(fd, (const sockaddr*)&address, sizeof(address)) != 0) {
        return false;
    }

    return true;
}
