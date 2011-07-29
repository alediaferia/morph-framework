#include "mfilemanager.h"
#include "fcntl.h"
#include <sys/stat.h>
#include <stdio.h>

MFileManager::MFileManager()
{
}


MFile* MFileManager::open(const char * path, int mode){

    MFile * file=new MFile();
    mode_t m;

    if (mode & ReadOnly) {
        m |= O_RDONLY;
    }
    if (mode & WriteOnly){
        m |=O_WRONLY;
    }
    if(mode & Truncate){
        m|=O_TRUNC;
    }

    if((file->m_fd = ::open(path, O_CREAT | m, 0644))==-1){
        return 0;
    }
    return file;
}

void MFileManager::rename(const char * oldPath, const char * newPath){
    ::rename(oldPath,newPath);
}

