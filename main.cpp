#include "mobject.h"
#include <iostream>


int main(int argc, char **argv)
{

    MObject *o = new MObject();

    M_INVOKE_SLOT(o, testSlot);

    M_INVOKE_SLOT1(o, setNumber, 48);

    std::cout << o->getNumber() << std::endl;

    delete o;

    return 0;
}
