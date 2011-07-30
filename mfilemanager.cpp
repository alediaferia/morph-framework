#include "mfilemanager.h"
#include "fcntl.h"
#include <sys/stat.h>
#include <stdio.h>

MFileManager::MRef MFileManager::s_instance = MFileManager::MRef(0);

MFileManager::MFileManager() : MObject()
{
}


int MFileManager::open(const char * path, int mode)
{
    mode_t m = 0;

    if (mode & MIODevice::ReadOnly) {
        m |= O_RDONLY;
    }
    if (mode & MIODevice::WriteOnly){
        m |=O_WRONLY;
    }
    if(mode & MIODevice::Truncate){
        m|=O_TRUNC;
    }

    int fd = ::open(path, m, 0644);
    
    // the file probably does not exist
    // so we try to open a new one
    if (fd == -1) {
        m |= O_CREAT;
        fd = ::open(path, m, 0644);
    }
    
    return fd;

}

bool MFileManager::rename(const char * oldPath, const char * newPath)
{
    if (::rename(oldPath,newPath) != -1) {
        return true;
    }
    
    return false;
}

MFileManager* MFileManager::defaultFileManager()
{
    if (!MFileManager::s_instance.data()) {
        MFileManager::s_instance = MFileManager::MRef(new MFileManager);
    }
    
    return (MFileManager*)MFileManager::s_instance.data();
}

void MFileManager::setDefaultFileManager(MFileManager::MRef fileManager)
{
    MFileManager::s_instance = fileManager;
}

bool MFileManager::mkdir(const char* path)
{
    return false;
}

MList<MString> MFileManager::listDir(const char *path)
{
    return MList<MString>();
}
