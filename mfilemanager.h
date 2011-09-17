#ifndef MFILEMANAGER_H
#define MFILEMANAGER_H

#include "mfile.h"
#include "mobject.h"
#include "mlist.h"
#include "miodevice.h"

class MFileManager : public MObject
{
    M_UNALLOCABLE_OBJECT(MFileManager)

public:
    static MFileManager* defaultFileManager();
    
    virtual int open(const char *path, int);
    virtual bool rename(const char*, const char* );
    virtual bool mkdir(const char* path);
    virtual MList::MRef listDir(const char *path);
    virtual bool copy(const char* from ,const char* to);

private:
    static MFileManager::MRef s_instance;
    class MFileManagerPrivate;
    MFileManagerPrivate *d;
    
protected:
    MFileManager();
};

#endif // MFILEMANAGER_H
