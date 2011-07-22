#ifndef MEVENTLOOP_H
#define MEVENTLOOP_H

class MEventLoop
{
public:
    MEventLoop();

    void run();
    void terminate();

private:
    class MEventLoopPrivate;
    MEventLoopPrivate *const d;
};

#endif // MEVENTLOOP_H
