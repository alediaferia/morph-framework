#include "mfilemanager.h"
#include "fcntl.h"
#include <sys/stat.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/dir.h>
#include <sys/param.h>
#include <copyfile.h>

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

bool MFileManager::mkdir(const char* path)
{
    if(::mkdir(path,0755)==-1){
        return false;
    }
    return true;
}

MList::MRef MFileManager::listDir(const char *path)
{
    struct dirent **files;
    int count=0;
    MList::MRef result = MList::alloc();

    count=::scandir(path,&files,NULL,NULL);

    for(int i=0; i<count; i++){
        result->append(MString::alloc()->init(files[i]->d_name));
    }

    return result;
}


bool MFileManager::copy(const char *from, const char *to){
    copyfile_state_t state;
    state = copyfile_state_alloc();

    if(::copyfile(from,to,state,COPYFILE_ALL)==-1){
        return false;
    }

    return true;
}
