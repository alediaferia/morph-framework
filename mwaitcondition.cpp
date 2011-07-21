#include "mwaitcondition.h"
#include <pthread.h>

#include "mmutex_p.h"

class MWaitCondition::MWaitConditionPrivate
{
public:
    MWaitConditionPrivate(MWaitCondition *m) :
        m(m)
    {
        pthread_cond_init(&nativeWaitCondition, 0);
    }

    MWaitCondition *m;
    pthread_cond_t nativeWaitCondition;
};

MWaitCondition::MWaitCondition() :
    d(new MWaitConditionPrivate(this))
{
}

MWaitCondition::~MWaitCondition()
{
    delete d;
}

bool MWaitCondition::wait(MMutex *mutex)
{
    pthread_cond_wait(&d->nativeWaitCondition, &mutex->d->mutex);
}

void MWaitCondition::signal()
{
    pthread_cond_signal(&d->nativeWaitCondition);
}
