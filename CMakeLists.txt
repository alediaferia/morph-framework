PROJECT(Morph)

SET(Morph_SOURCES
mobject.cpp
main.cpp
mobjectwatcher.cpp
mvariable.cpp
mstring.cpp
mlist.cpp
mutils.cpp
mthread.cpp
mmutex.cpp
msocket.cpp
mserversocket.cpp
mqueue.cpp
mwaitcondition.cpp
mevent.cpp
meventloop.cpp
#marray.cpp
#mdictionary.cpp
#massociativearray.cpp
)
#ADD_LIBRARY(morph SHARED ${Morph_SOURCES})
ADD_EXECUTABLE(morph ${Morph_SOURCES})
