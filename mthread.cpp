#include "mthread.h"
#include <pthread.h>

#include <iostream>
#include "mutils.h"
#include "mmutex.h"

class MThread::Private {
public:
    Private(MThread *m) :
        m(m),
        finished(true)
    {}

    MThread *m;
    bool finished;
    MMutex threadMutex;
};

void* runThread(void* mthread)
{
    MThread *thread = static_cast<MThread*>(mthread);
    thread->run();

    thread->d->threadMutex.lock();
    thread->d->finished = true;
    thread->d->threadMutex.unlock();

    return 0;
}

static const int s_thread_loop_cycle_time = 50000; // usecs

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
    d->threadMutex.lock();
    d->finished = false;
    d->threadMutex.unlock();

    pthread_t pthread;
    pthread_create(&pthread, 0, runThread, (void*)this);
}

void MThread::wait()
{
    while (1) {
        d->threadMutex.lock();
        if (d->finished) {
            d->threadMutex.unlock();
            return;
        }
        d->threadMutex.unlock();
        usleep(s_thread_loop_cycle_time);
    }
}
