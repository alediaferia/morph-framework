#include "mthread.h"
#include <pthread.h>

#include <iostream>
#include "mutils.h"

class MThread::Private {
public:
    Private(MThread *m) :
        m(m),
        finished(true)
    {}

    MThread *m;
    bool finished;
};

void* runThread(void* mthread)
{
    MThread *thread = static_cast<MThread*>(mthread);
    thread->run();
    thread->d->finished = true;

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
    d->finished = false;
    pthread_t pthread;
    pthread_create(&pthread, 0, runThread, (void*)this);
}

void MThread::wait()
{
    while (!d->finished) {
    }
}
