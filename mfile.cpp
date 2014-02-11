#include "mfile.h"
#include "mfilemanager.h"

class MFile::MFilePrivate
{
public:
    MFilePrivate(MFile *m) :
        m(m)
    {}
    
    MFile *m;
};

MFile::MFile() : MIODevice(),
    d(new MFilePrivate(this))
{
}

bool MFile::open(const MString::MRef path, int mode)
{
    const char *cstringpath = path->data();
    int fd = MFileManager::defaultFileManager()->open(cstringpath, mode);
    if (fd == -1) {
        return false;
    }
    
    setDescriptor(fd);
    return true;
}
