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

    /**
     * Listeners will be notified when
     * new data is ready to be read through
     * invokable void readyRead(MNumber::MRef availableBytes);
     */
    void addReadyReadListener(mref listener);

    bool waitForReadyRead();

    ssize_t availableBytes() const;

private:
    class MSocketPrivate;
    MSocketPrivate *d;
};

#endif // MSOCKET_H
