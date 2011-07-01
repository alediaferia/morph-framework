#include "mobject.h"
#include <iostream>


int main(int argc, char **argv)
{

    MObject *o = new MObject();

    o->connect("clicked", M_SLOT(o, testSlot));

    o->clicked();

    delete o;

    return 0;
}
