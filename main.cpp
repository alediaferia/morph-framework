#include <iostream>
#include "mlist.h"
#include "mstring.h"
#include "mobject.h"

#include "mthread.h"
#include "mutils.h"

class MyThread : public MThread
{
protected:
    void run() {
        int i = 5;
        while (i > 0) {
            mPrint("Hello");
            i--;
            sleep(1);
        }
    }
};

int main(int argc, char **argv)
{
    MyThread *t = new MyThread();
    t->start();
    t->wait();

    delete t;

    return 0;
}
