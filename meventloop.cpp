#include "meventloop.h"
#include "mqueue.h"
#include "mevent.h"
#include "mmutex.h"
#include "mwaitcondition.h"

class MEventLoop::MEventLoopPrivate
{
public:
    MEventLoopPrivate(MEventLoop* m) :
        m(m),
        terminate(false)
    {}

    bool terminate;
    MQueue<MEvent*> eventQueue;
    MMutex mutex;
    MWaitCondition waitCondition;
};

MEventLoop::MEventLoop()
{
}

void MEventLoop::run()
{
    while (!d->terminate) {
        // wait condition here
        // so the process does not
        // get all CPU while waiting

        if (!d->eventQueue.isEmpty()) {
            MEvent *event = d->eventQueue.dequeue();
            // process event here
        }
    }
}
