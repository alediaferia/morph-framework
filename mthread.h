#ifndef MTHREAD_H
#define MTHREAD_H

#include "mobject.h"

class MThread : public MObject
{
public:
    M_OBJECT(MThread)

    MThread();
    ~MThread();

    M_INVOKABLE void start();
    void wait();

    bool finished() const;

    //static MThread* currentThread();

protected:
    virtual void run();

private:
    friend void* runThread(void*);
    class MThreadPrivate;
    MThreadPrivate * const d;
};

#endif // MTHREAD_H
