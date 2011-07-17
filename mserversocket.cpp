
#include "mserversocket.h"
#include "mstring.h"


MServerSocket::MServerSocket ( int port )
{
    if ( ! MSocket::create() )
    {
        std::cout<<"Error create"<<std::endl;
    }

    if ( ! MSocket::bind ( port ) )
    {
        std::cout<<"Error bind"<<std::endl;
    }

    if ( ! MSocket::listen() )
    {
        std::cout<<"Error listen"<<std::endl;
    }

}

MServerSocket::~MServerSocket()
{
}


const MServerSocket& MServerSocket::operator << ( MString& s ) const
{
    if ( ! MSocket::send (s.data()))
    {
        std::cout<<"Error send"<<std::endl;
    }

    return *this;

}


const MServerSocket& MServerSocket::operator >> ( MString& s ) const
{
    if ( ! MSocket::recv (s))
    {
        std::cout<<"Error receive"<<std::endl;
    }

    return *this;
}

void MServerSocket::accept ( MServerSocket& sock )
{
    if ( ! MSocket::accept ( sock ) )
    {
        std::cout<<"Error accept"<<std::endl;
    }
}
