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

    /**
     * This method blocks the current thread
     * until new data is available.
     * If the parameter synchronously is false a
     * dedicated thread will be created to wait and this
     * method will immediately return true.
     * As soon as new data is read to be read the invokable
     * "readyRead" will be called on each registered listener.
     * @see addReadyReadListener
     */
    bool waitForReadyRead(bool synchronously = true);

    ssize_t availableBytes() const;

private:
    class MSocketPrivate;
    MSocketPrivate *d;
};

#endif // MSOCKET_H
