#include "mutils.h"
#include <iostream>
#include "mmutex.h"

MMutex mutils_print_mutex;

void mPrint(const char *message)
{
    mutils_print_mutex.lock();
    std::cout << message << std::endl;
    mutils_print_mutex.unlock();
}

