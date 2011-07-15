#include "mthread.h"
#include <pthread.h>

#include <iostream>
#include "mutils.h"

class MThread::Private {
public:
    Private(MThread *m) :
        m(m)
    {}

    MThread *m;
};

void* runThread(void* mthread)
{
    MThread *thread = static_cast<MThread*>(mthread);
    thread->run();

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
    pthread_t pthread;
    pthread_create(&pthread, 0, runThread, (void*)this);
}
