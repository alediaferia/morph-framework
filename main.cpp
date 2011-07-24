#include <iostream>
#include "mlist.h"
#include "mstring.h"
#include "mobject.h"

#include "mthread.h"
#include "mutils.h"

int main(int argc, char **argv)
{

    MList<int> list;

    list.append(43).append(21).append(12).append(56);

    std::cout << list << std::endl;

    MList<int>::Iterator it = list.begin();
    for(; it != list.end(); ++it) {
        if (it.value() == 21) {
            it = list.remove(it);
        }
    }

    std::cout << list << std::endl;

    return 0;
}
