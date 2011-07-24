#ifndef MEVENTLOOP_H
#define MEVENTLOOP_H

#include "mobject.h"

class MEvent;
class MObject;

class MEventLoop
{
public:
    MEventLoop();

    /**
     * Starts the event loop
     */
    void run();

    /**
     * Immediately terminates
     * the event loop
     * discarding every eventual event
     * in the queue.
     */
    void terminate();

    /**
     * Waits for all events currently
     * in the queue to be processed
     * and then quits.
     */
    void quitLater();

    /**
     * Sends an event to the event queue
     * for the given receiver.
     * The event will be processed
     * as soon as all previous events
     * have been processed.
     */
    void sendEvent(mref, MEvent*);

    static MEventLoop* globalEventLoop();

private:
    static MEventLoop s_globalEventLoop;

    class MEventLoopPrivate;
    MEventLoopPrivate *const d;
};

#endif // MEVENTLOOP_H
