#include "mthread.h"
#include <pthread.h>

#include <iostream>
#include "mutils.h"
#include "mmutex.h"
#include "mwaitcondition.h"

static MThread* s_currentThread = 0;

class MThread::MThreadPrivate {
public:
    MThreadPrivate(MThread *m) :
        m(m),
        finished(true)
    {
    }

    MThread *m;
    bool finished;
    MMutex threadMutex;
    MWaitCondition waitCondition;
};

void* runThread(void* mthread)
{
    MThread *thread = static_cast<MThread*>(mthread);

    thread->run();
    thread->d->threadMutex.lock();
    thread->d->finished = true;

    thread->d->waitCondition.signal();
    thread->d->threadMutex.unlock();

    return 0;
}

MThread::MThread() :
    d(new MThreadPrivate(this))
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
    while (!d->finished) {
        d->waitCondition.wait(&d->threadMutex);
    }
}

bool MThread::finished() const
{
    return d->finished;
}
