#ifndef MCLIENTSOCKET_H
#define MCLIENTSOCKET_H

#include "msocket.h"

class MClientSocket : public MSocket
{
public:
    M_OBJECT(MClientSocket)

    MClientSocket();

    void connect();
};

#endif // MCLIENTSOCKET_H
