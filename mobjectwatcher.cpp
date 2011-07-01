#include "mobjectwatcher.h"

#include <iostream>

#include "mobject.h"

MObjectWatcher::MObjectWatcher() :
    m_dying(false)
{
}

MObjectWatcher::~MObjectWatcher()
{
    //std::cout << "MObjectWatcher is dying" << std::endl;
    m_dying = true;

    // iterate over all elements calling their destructor
    std::list<MObject*>::iterator it = m_objects.begin();
    for (; it != m_objects.end(); ++it) {
        delete *it;
    }

    m_objects.clear();
}

MObjectWatcher MObjectWatcher::s_instance = MObjectWatcher();

MObjectWatcher* MObjectWatcher::instance()
{
    return &s_instance;
}

void MObjectWatcher::registerObject(MObject *object)
{
    m_objects.push_back(object);
}

void MObjectWatcher::objectDeleted(MObject *object)
{
    if (m_dying) {
        return;
    }

    std::list<MObject*>::iterator it = m_objects.begin();
    for (; it != m_objects.end(); ++it) {
        if (*it == object) {
            m_objects.erase(it);
            //std::cout << "deleted object " << object << " removed from watch list" << std::endl;
            return;
        }
    }
}
