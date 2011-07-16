#include "mmutex.h"
#include <pthread.h>

class MMutex::Private
{
public:
    Private(MMutex *m) :
        m(m),
        mutex()
    {
        pthread_mutex_init(&mutex, 0);
    }

    MMutex *m;
    pthread_mutex_t mutex;
};

MMutex::MMutex() : d(new Private(this))
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
