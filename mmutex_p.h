#ifndef MMUTEX_P_H
#define MMUTEX_P_H

class MMutex::MMutexPrivate
{
public:
    MMutexPrivate(MMutex *m) :
        m(m),
        mutex()
    {
        pthread_mutex_init(&mutex, 0);
    }

    MMutex *m;
    pthread_mutex_t mutex;
};


#endif // MMUTEX_P_H
