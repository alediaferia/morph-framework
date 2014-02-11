#ifndef MIODEVICE_H
#define MIODEVICE_H

#include "mobject.h"
#include "mstring.h"

class MIODevice : public MObject
{
    M_UNALLOCABLE_OBJECT(MIODevice)
public:
    enum OpenMode {
        ReadOnly=0x0001,
        WriteOnly=0x0002,
        Append=0x0004,
        Truncate=0x0008,
        ReadWrite=ReadOnly | WriteOnly
    };

    virtual ~MIODevice();

    bool seek(off_t offset);
    bool seekable() const;
    int descriptor() const;

	int write(const MString::MRef data);
    MString::MRef read(int size);

    bool close();

    void setDescriptor(int fd);
protected:
    MIODevice();

    void setSeekable(bool seekable);

    virtual int readPlainData(char* buffer, size_t size);
    virtual int writePlainData(const char* buffer, size_t size);

private:
    class MIODevicePrivate;
    MIODevicePrivate *d;
};

#endif // MIODEVICE_H
