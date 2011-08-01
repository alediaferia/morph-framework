#ifndef MSOCKET_H
#define MSOCKET_H

#include "miodevice.h"

class MSocket : public MIODevice
{
    M_OBJECT(MSocket)
public:
    MSocket();
    virtual ~MSocket();

    void setAddress(const MString &address);
    MString address() const;

    void setPort(uint16_t port);
    uint16_t port() const;

    bool connect();

private:
    class MSocketPrivate;
    MSocketPrivate *d;
};

#endif // MSOCKET_H
