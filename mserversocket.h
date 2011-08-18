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

    /**
     * Connection listeners must be valid MObjects
     * with an invokable method with the following
     * signature: void clientConnected(mref clientSocket);
     * @note: ownership of clientSocket is left to the receiving
     * object
     */
    void addConnectionListener(mref listener);

protected:
    void clientConnected(int clientSockD, sockaddr_in incomingAddress);

private:
    class MServerSocketPrivate;
    MServerSocketPrivate *d;

    friend class AcceptThread;
};



#endif // MSERVERSOCKET_H
