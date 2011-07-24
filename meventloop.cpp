#include "meventloop.h"
#include "mqueue.h"
#include "mevent.h"
#include "mmutex.h"
#include "mwaitcondition.h"
#include "mpair.h"
#include "mobject.h"

MEventLoop MEventLoop::s_globalEventLoop = MEventLoop();

class MEventLoop::MEventLoopPrivate
{
public:
    MEventLoopPrivate(MEventLoop* m) :
        m(m),
        terminate(false),
        running(false),
        quitLater(false)
    {}

    MEventLoop *m;
    bool terminate;
    bool running;
    bool quitLater;
    MQueue<MPair<MObject*,MEvent*> > eventQueue;
    MMutex mutex;
    MWaitCondition waitCondition;
};

MEventLoop::MEventLoop() :
    d(new MEventLoopPrivate(this))
{
}

MEventLoop* MEventLoop::globalEventLoop()
{
    return &s_globalEventLoop;
}

void MEventLoop::sendEvent(MObject *receiver, MEvent *event)
{
    d->mutex.lock();
    d->eventQueue.enqueue(MPair<MObject*, MEvent*>(receiver, event));
    d->waitCondition.signal();
    d->mutex.unlock();
}

void MEventLoop::terminate()
{
    d->mutex.lock();
    d->terminate = true;
    d->waitCondition.signal();
    d->mutex.unlock();
}

void MEventLoop::quitLater()
{
    d->mutex.lock();
    d->quitLater = true;
    d->waitCondition.signal();
    d->mutex.unlock();
}

void MEventLoop::run()
{
    if (d->running) {
        return;
    }

    d->running = true;

    while (!d->terminate) {
        if (d->eventQueue.isEmpty() && d->quitLater) {
            break;
        }

        if (!d->eventQueue.isEmpty()) {
            MPair<MObject*, MEvent*> eventPair = d->eventQueue.dequeue();
            // process event here
            eventPair.left->processEvent(eventPair.right);
        } else {
            // wait condition here
            // so the process does not
            // get all CPU while waiting
            d->waitCondition.wait(&d->mutex);
        }
    }
}
