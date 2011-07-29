#include "mfile.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <iostream>


MFile::MFile()
{

}

void MFile::close() const{
    ::close(m_fd);
}

void MFile::write(const char * std){
    ssize_t bytes_written;
    bytes_written = ::write(m_fd, std,strlen(std));
}
