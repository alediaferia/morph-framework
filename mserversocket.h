#ifndef MSERVERSOCKET_H
#define MSERVERSOCKET_H

#include "msocket.h"
#include "mstring.h"

#include <netinet/in.h>
#include <arpa/inet.h>

class MServerSocket : public MSocket
{
public:
    M_OBJECT(MServerSocket)

    MServerSocket();
    ~MServerSocket();

    void start();

    void addConnectionListener(mref listener);


    MString read(int size);
    int write(const MString &);

protected:
    void clientConnected(int clientSockD, sockaddr incomingAddress);

private:
    class MServerSocketPrivate;
    MServerSocketPrivate *d;

    friend class AcceptThread;
};



#endif // MSERVERSOCKET_H
