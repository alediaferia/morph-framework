#ifndef MMUTEX_H
#define MMUTEX_H

class MMutex
{
public:
    MMutex();
    ~MMutex();

    void lock();
    void unlock();

private:
    class MMutexPrivate;
    MMutexPrivate *const d;

    friend class MWaitCondition;

};

#endif // MMUTEX_H
