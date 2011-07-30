#include "mfile.h"

int main(int argc, char **argv)
{
    MFile::MRef file = MFile::alloc();
    file->open("/Users/alediaferia/Desktop/morph-file.txt", MIODevice::WriteOnly);
    
    file->write("Hey questo è morph!!");
}
