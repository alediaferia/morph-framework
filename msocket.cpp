#include "msocket.h"
#include <fcntl.h>


MSocket::MSocket() :
    m_sock ( -1 )
{
    memset ( &m_addr,0,sizeof ( m_addr ) );
}

MSocket::~MSocket()
{
    if ( is_valid())
        ::close ( m_sock );
}

bool MSocket::create()
{
    m_sock = socket ( AF_INET,SOCK_STREAM,0 );

    if ( ! is_valid() )
        return false;

    int on = 1;
    if ( setsockopt ( m_sock, SOL_SOCKET, SO_REUSEADDR, ( const char* ) &on, sizeof ( on ) ) == -1 )
        return false;
    return true;
}



bool MSocket::bind ( const int port )
{
    if ( ! is_valid() )
    {
        return false;
    }

    m_addr.sin_family = AF_INET;
    m_addr.sin_addr.s_addr = INADDR_ANY;
    m_addr.sin_port = htons ( port );

    int bind_return = ::bind ( m_sock,( struct sockaddr * ) &m_addr,sizeof ( m_addr ) );

    if ( bind_return == -1 )
    {
        return false;
    }
    return true;
}


bool MSocket::listen() const
{
    if ( ! is_valid() )
    {
        return false;
    }

    int listen_return = ::listen ( m_sock, MAXCONNECTIONS );

    if ( listen_return == -1 )
    {
        return false;
    }

    return true;
}


bool MSocket::accept ( MSocket& new_socket ) const
{
    int addr_length = sizeof ( m_addr );
    new_socket.m_sock = ::accept ( m_sock, ( sockaddr * ) &m_addr, ( socklen_t * ) &addr_length );

    if ( new_socket.m_sock <= 0 )
        return false;
    else
        return true;
}


bool MSocket::send ( const char* s ) const
{
    int status = ::send (m_sock, s, strlen(s), MSG_NOSIGNAL );
    if ( status == -1 )
    {
        return false;
    }
    else
    {
        return true;
    }
}


int MSocket::recv ( MString& s ) const
{
    char buf [ MAXRECV + 1 ];
    s = "";

    memset ( buf, 0, MAXRECV + 1 );
    int status = ::recv ( m_sock, buf, MAXRECV, 0 );

    if ( status == -1 )
    {
        return 0;
    }
    else if ( status == 0 )
    {
        return 0;
    }
    else
    {
        s = buf;
        return status;
    }
}


bool MSocket::connect ( const char* host, const int port )
{
    if ( ! is_valid() ) return false;

    m_addr.sin_family = AF_INET;
    m_addr.sin_port = htons ( port );

    int status = inet_pton ( AF_INET, host, &m_addr.sin_addr );

    status = ::connect (m_sock,( sockaddr *) &m_addr, sizeof (m_addr));

    if ( status == 0 )
        return true;
    else
        return false;
}

void MSocket::set_non_blocking ( const bool b )
{
    int opts;
    opts = fcntl ( m_sock,F_GETFL );

    if ( opts < 0 )
    {
        return;
    }

    if ( b )
        opts = ( opts | O_NONBLOCK );
    else
        opts = ( opts & ~O_NONBLOCK );

    fcntl ( m_sock, F_SETFL,opts );
}
