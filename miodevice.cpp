#include "miodevice.h"
#include "miodevice_p.h"

MIODevice::MIODevice() :
    d(new MIODevicePrivate(this))
{
}

void MIODevice::setDescriptor(int fd)
{
    d->fd = fd;
}

int MIODevice::descriptor() const
{
    return d->fd;
}

int MIODevice::write(const MString &data)
{
    return writePlainData(data.data(), data.size());
}

bool MIODevice::seek(off_t offset)
{
    if (lseek(d->fd, offset, SEEK_SET) == -1) {
        return false;
    }
    
    return true;
}

MString MIODevice::read(int size)
{
    char buffer[size];
    int read = readPlainData(buffer, size);

    return MString(buffer, read);
}

bool MIODevice::close()
{
    if (::close(d->fd) != 0) {
        return false;
    }

    return true;
}

int MIODevice::writePlainData(const char *buffer, size_t size)
{
    return ::write(d->fd, buffer, size);
}

int MIODevice::readPlainData(char *buffer, size_t size)
{
    return ::read(d->fd, buffer, size);
}
