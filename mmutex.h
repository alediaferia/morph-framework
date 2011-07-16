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
    class Private;
    Private *const d;
};

#endif // MMUTEX_H
