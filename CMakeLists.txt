PROJECT(Morph)

SET(Morph_SOURCES
mobject.cpp
main.cpp
mobjectwatcher.cpp
mvariable.cpp
mstring.cpp
)
#ADD_LIBRARY(morph SHARED ${Morph_SOURCES})
ADD_EXECUTABLE(morph ${Morph_SOURCES})
