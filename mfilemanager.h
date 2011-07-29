#ifndef MFILEMANAGER_H
#define MFILEMANAGER_H

#include "mfile.h"

class MFileManager
{
public:
    enum OpenMode {
        ReadOnly=0x0001,
        WriteOnly=0x0002,
        Append=0x0004,
        Truncate=0x0008,
        ReadWrite=ReadOnly | WriteOnly
    };

    MFileManager();

    MFile* open(const char*, int);
    void rename(const char*,const char* );
};

#endif // MFILEMANAGER_H
