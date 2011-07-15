#include "mvariable.h"

MVariable::MVariable() :
    d(MSharedPtr<PrivateVariable>(new PrivateVariable(this)))
{
}

MVariable::MVariable(const MVariable &copy) :
    d(copy.d)
{}

MVariable::MVariable(const char *data) :
    d(MSharedPtr<PrivateVariable>(new PrivateVariable(this)))
{
    d->initWithData<MString>((void*)data);
}

MVariable::MVariable(int data) :
    d(MSharedPtr<PrivateVariable>(new PrivateVariable(this)))
{
    std::cout << "int ctor" << std::endl;
    d->initWithData<int>((void*)&data);
}

MVariable::MVariable(unsigned int data) :
    d(MSharedPtr<PrivateVariable>(new PrivateVariable(this)))
{
    d->initWithData<unsigned int>((void*)&data);
}

MVariable::MVariable(unsigned long int data) :
    d(MSharedPtr<PrivateVariable>(new PrivateVariable(this)))
{
    d->initWithData<unsigned long int>((void*)&data);
}

MVariable::MVariable(bool data) :
    d(MSharedPtr<PrivateVariable>(new PrivateVariable(this)))
{
    d->initWithData<bool>((void*)&data);
}

MVariable::MVariable(char data) :
    d(MSharedPtr<PrivateVariable>(new PrivateVariable(this)))
{
    d->initWithData<char>((void*)&data);
}

MVariable::MVariable(const MString &data) :
    d(MSharedPtr<PrivateVariable>(new PrivateVariable(this)))
{
    d->initWithData<MString>((void*)&data);
}

MVariable::~MVariable()
{
}

MVariable& MVariable::operator =(const MVariable &copy)
{
    d = copy.d;
}

bool MVariable::isEmpty() const
{
    return d->empty;
}

bool MVariable::isValid() const
{
    return d->valid;
}

MString MVariable::toString() const
{
    return value<MString>();
}

int MVariable::toInt() const
{
    return value<int>();
}

bool MVariable::toBool() const
{
    return value<bool>();
}
