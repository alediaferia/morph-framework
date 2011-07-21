#ifndef MTHREAD_H
#define MTHREAD_H

class MThread
{
public:
    MThread();
    ~MThread();

    void start();
    void wait();

protected:
    virtual void run();

private:
    friend void* runThread(void*);
    class MThreadPrivate;
    MThreadPrivate * const d;
};

#endif // MTHREAD_H
