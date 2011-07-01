#ifndef MOBJECTWATCHER_H
#define MOBJECTWATCHER_H

#include <list>

class MObject;

class MObjectWatcher
{
public:
    static MObjectWatcher *instance();
    ~MObjectWatcher();

private:
    void registerObject(MObject *);
    void objectDeleted(MObject *);

private:
    MObjectWatcher();
    static MObjectWatcher s_instance;

    std::list<MObject*> m_objects;

    bool m_dying;

    friend class MObject;
};

#endif // MOBJECTWATCHER_H
