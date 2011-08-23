#include "mmutex.h"
#include <pthread.h>

#include "mmutex_p.h"

MMutex::MMutex() : MObject(),
    d(new MMutexPrivate(this))
{
}

MMutex::~MMutex()
{
    delete d;
}

void MMutex::lock()
{
    pthread_mutex_lock(&d->mutex);
}

void MMutex::unlock()
{
    pthread_mutex_unlock(&d->mutex);
}
