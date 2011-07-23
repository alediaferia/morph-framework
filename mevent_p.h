#ifndef MEVENT_P_H
#define MEVENT_P_H

class MEvent::MEventPrivate
{
public:
    MEventPrivate(MEvent *m) :
        m(m)
    {}

    MEvent *m;
    MEvent::Type type;
};

#endif // MEVENT_P_H
