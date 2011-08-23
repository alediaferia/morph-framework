#ifndef MSOCKET_H
#define MSOCKET_H

#include "miodevice.h"
#include "mstring.h"

class MSocket : public MIODevice
{
    M_OBJECT(MSocket)
public:
    MSocket();
    virtual ~MSocket();

    void setAddress(MString::MRef address);
    MString::MRef address() const;

    void setPort(uint16_t port);
    uint16_t port() const;

    bool connect();

private:
    class MSocketPrivate;
    MSocketPrivate *d;
};

#endif // MSOCKET_H
