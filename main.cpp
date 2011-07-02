#include <iostream>
#include "mlist.h"
#include "mstring.h"


int main(int argc, char **argv)
{

    MString s;
    s="Ciao";
    MList<MString> list;

    list.appendToLast("one");
    list.appendToLast("two");
    list.appendToLast("three");


    std::cout<<list.get(0);
    return 0;
}
