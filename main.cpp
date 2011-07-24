#include <iostream>
#include "mlist.h"
#include "mstring.h"
#include "mobject.h"

#include "mthread.h"
#include "mutils.h"
#include "mpair.h"
#include "meventloop.h"
#include "massociativearray.h"
#include "mevent.h"

class MyThread : public MThread
{
public:
    MyThread(MObject *parent = 0) : MThread(parent),
        m_count(0)
    {}

    ~MyThread()
    {
    }
protected:
    void run() {
        while (m_count < 5) {
            std::cout << m_count << std::endl;
            m_count++;
            sleep(1);
        }

        MEventLoop::globalEventLoop()->quitLater();
    }

private:
    int m_count;
};

int main(int argc, char **argv)
{

    MObject::MRef object = new MObject;
    object->id = "object";
    MEventLoop *mainEventLoop = MEventLoop::globalEventLoop();

    MEvent e(MEvent::ApplicationStartedEvent);

    mainEventLoop->sendEvent(object, &e);

    MThread::MRef thread = new MyThread;
    thread->id = "thread";
    thread->start();

    mainEventLoop->run();

    return 0;
}
