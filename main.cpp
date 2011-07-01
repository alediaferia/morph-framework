#include "mobject.h"
#include "mobjectwatcher.h"
#include <iostream>

#include "mvariable.h"
#include "mstring.h"

class MyClass {
public:
    MyClass() : m_value(0)
    {
        std::cout << "ctor" << std::endl;
    }

    MyClass(const MyClass &c) :
    m_value(c.m_value)
    {}

    MyClass(int i) :
        m_value(i)
    {}

    ~MyClass() {}

    static int test;

    int value() const
    {
        return m_value;
    }

private:
    int m_value;
};

M_DECLARE_TYPE(MyClass)


class MyDelegate : public MObjectDelegate
{
public:
    void destroyed(MObject *o)
    {
        std::cout << "object " << o << " destroyed" << std::endl;
        delete this;
    }
};

class Button : public MObject
{
public:
    Button() : MObject()
    {}
};

int main(int argc, char **argv)
{
    MVariable a;
    a.setValue<MyClass>(MyClass(34));

    return 0;
}
