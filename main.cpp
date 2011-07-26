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
#include "mserversocket.h"

class MyThread : public MThread
{
public:
    M_OBJECT(MyThread)
    MyThread() : MThread(),
        m_count(5)
    {}

    static MyThread::MRef alloc()
    {
        return MyThread::MRef(new MyThread);
    }

protected:
    void run() {
        while (m_count > 0) {
            std::cout << m_count << std::endl;
            m_count--;
            sleep(1);
        }
    }

private:
    int m_count;
};

int main(int argc, char **argv)
{

    MyThread *t = new MyThread;
    t->invokableByName("start")->invoke();

    t->wait();

    return 0;
}
