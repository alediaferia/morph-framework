#ifndef MWAITCONDITION_H
#define MWAITCONDITION_H

#include "mmutex.h"

class MWaitCondition : public MObject
{
    M_OBJECT(MWaitCondition)
public:
    MWaitCondition();
    ~MWaitCondition();

    bool wait(MMutex::MRef mutex);
    void signal();

private:
    class MWaitConditionPrivate;
    MWaitConditionPrivate *const d;
};

#endif // MWAITCONDITION_H
