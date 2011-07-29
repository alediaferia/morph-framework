#include <iostream>
#include "mlist.h"
#include "mstring.h"
#include "mobject.h"

#include "mthread.h"
#include "mutils.h"
#include "mpair.h"
#include "meventloop.h"
#include "massociativearray.h"
#include "mevent.h"
#include "mserversocket.h"

class MyObject : public MObject
{
    M_OBJECT(MyObject)
public:
    MyObject()
    {
        registerInvokable(M_INVOKABLE1(MyObject, sayHello));
    }

    void sayHello(const char* name)
    {
        printf("Hello %s!!!\n", name);
    }
};

int main(int argc, char **argv)
{
    MyObject::MRef object = MyObject::alloc();
    object->invokableByName("sayHello")->invoke(M_ARG("Alessandro"));
    return 0;
}
