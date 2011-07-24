#include <iostream>
#include "mlist.h"
#include "mstring.h"
#include "mobject.h"

#include "mthread.h"
#include "mutils.h"
#include "mpair.h"

#include "massociativearray.h"

int main(int argc, char **argv)
{
    MAssociativeArray<MString, int> map;

    map.insert("antonio", 28);
    map.insert("alessandro", 30);
    map.insert("ruggiero", 24);

    std::cout << "alessandro: " << map.value("alessandro") << std::endl;

    map["alessandro"] = 29;

    std::cout << "alessandro: " << map.value("alessandro") << std::endl;

    return 0;
}
