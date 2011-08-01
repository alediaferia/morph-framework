#include "miodevice.h"
#include "miodevice_p.h"

MIODevice::MIODevice() :
    d(new MIODevicePrivate(this))
{
    d->seekable = true;
}

MIODevice::~MIODevice()
{
    close();
    delete d;
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
    if (!d->fd) {
        return 0;
    }

    return writePlainData(data.data(), data.size());
}

bool MIODevice::seek(off_t offset)
{
    if (!seekable()) {
        return false;
    }

    if (lseek(d->fd, offset, SEEK_SET) == -1) {
        return false;
    }
    
    return true;
}

void MIODevice::setSeekable(bool seekable)
{
    d->seekable = seekable;
}

bool MIODevice::seekable() const
{
    return d->seekable;
}

MString MIODevice::read(int size)
{
    if (!d->fd) {
        return MString();
    }

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
