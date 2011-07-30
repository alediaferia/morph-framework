#ifndef MFILE_H
#define MFILE_H

#include "miodevice.h"

class MFile : public MIODevice
{
    M_OBJECT(MFile)
public:
    MFile();
    bool open(const MString &path, int mode);
    
private:
    class MFilePrivate;
    MFilePrivate *d;
};

#endif // MFILE_H
