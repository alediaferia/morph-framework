#ifndef MSERVERSOCKET_H
#define MSERVERSOCKET_H

#include "msocket.h"
#include "mstring.h"

class MServerSocket : private MSocket
{
public:

    MServerSocket ( int port );
    MServerSocket(){}
    virtual ~MServerSocket();

    const MServerSocket& operator << (  MString& ) const;
    const MServerSocket& operator >> ( MString& ) const;

    void accept ( MServerSocket& );

};



#endif // MSERVERSOCKET_H
