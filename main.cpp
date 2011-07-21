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

    list.append(65);
    list.append(54);
    list.append(61);
    list.append(76);
    std::cout << "size: " <<  list.size() << std::endl;

    while (1) {
        if (!list.size()) {
            break;
        }

        int value = list.pickAt(0);
        std::cout << "picked value " << value << std::endl;
    }

    return 0;
}
