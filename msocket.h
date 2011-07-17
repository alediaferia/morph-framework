#ifndef MSOCKET_H
#define MSOCKET_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "mstring.h"

const int MAXHOSTNAME = 200;
const int MAXCONNECTIONS = 5;
const int MAXRECV = 500;
const int MSG_NOSIGNAL = 0;

class MSocket
{
public:
    MSocket();
     virtual ~MSocket();

    bool create();
    bool bind ( const int port );
    bool listen() const;
    bool accept ( MSocket& ) const;

    bool connect ( const char* host, const int port );

    bool send ( const char* ) const;
    int recv ( MString& ) const;

    void setNoBlocking ( const bool );
    bool isValid() const { return m_socket != -1; }

private:

    int m_socket;
    sockaddr_in m_addr;
};

#endif // MSOCKET_H
