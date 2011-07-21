#include <iostream>
#include "mlist.h"
#include "mstring.h"
#include "mobject.h"

#include "mthread.h"
#include "mutils.h"

int main(int argc, char **argv)
{
    MList<int> list;

    list.insert(0, 23);

    std::cout << "size: " <<  list.size() << std::endl;

    list.insert(0, 65);

    std::cout << "size: " <<  list.size() << std::endl;

    std::cout << list.get(0) << " " << list.get(1) << std::endl;

    return 0;
}
