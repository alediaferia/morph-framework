#include "mthread.h"
#include <pthread.h>

#include <iostream>
#include "mutils.h"

class MThread::Private {
public:
    Private(MThread *m) :
        m(m),
        finished(true)
    {
        pthread_mutex_init(&threadMutex, 0);
    }

    MThread *m;
    bool finished;
    pthread_mutex_t threadMutex;
    pthread_cond_t waitCondition;
};

void* runThread(void* mthread)
{
    MThread *thread = static_cast<MThread*>(mthread);

    // initializing waitg condition for wait method
    pthread_cond_init(&thread->d->waitCondition, 0);
    thread->run();

    pthread_mutex_lock(&thread->d->threadMutex);
    thread->d->finished = true;
    pthread_cond_signal(&thread->d->waitCondition);
    pthread_mutex_unlock(&thread->d->threadMutex);

    return 0;
}

MThread::MThread() :
    d(new Private(this))
{
}

MThread::~MThread()
{
    delete d;
}

void MThread::run()
{
}

void MThread::start()
{
    pthread_mutex_lock(&d->threadMutex);
    d->finished = false;
    pthread_mutex_unlock(&d->threadMutex);

    pthread_t pthread;
    pthread_create(&pthread, 0, runThread, (void*)this);
}

void MThread::wait()
{
    while (!d->finished) {
        pthread_cond_wait(&d->waitCondition, &d->threadMutex);
    }

    pthread_mutex_unlock(&d->threadMutex);
}
