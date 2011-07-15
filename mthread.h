#ifndef MTHREAD_H
#define MTHREAD_H

class MThread
{
public:
    MThread();
    ~MThread();

    void start();

protected:
    virtual void run();

private:
    friend void* runThread(void*);
    friend class Private;
    Private * const d;
};

#endif // MTHREAD_H
