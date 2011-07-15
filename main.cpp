#include <iostream>
#include "mlist.h"
#include "mstring.h"
#include "mobject.h"

#include <iostream>
#include "mthread.h"
#include "mutils.h"

class MyThread : public MThread
{
public:
    MyThread() :
        count(0)
    {}
private:
    int count;

protected:
    void run()
    {
        while (count < 5) {
            mPrint("thread");
            count++;
            sleep(2);
        }
    }
};

int main(int argc, char **argv)
{
    MyThread *thread = new MyThread();
    thread->start();
    thread->wait();

    delete thread;

    return 0;
}
