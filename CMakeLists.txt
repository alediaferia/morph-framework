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
)
#ADD_LIBRARY(morph SHARED ${Morph_SOURCES})
ADD_EXECUTABLE(morph ${Morph_SOURCES})
