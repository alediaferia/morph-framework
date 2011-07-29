#include "minvokablemethod.h"
#include "mobject_macros.h"

void MInvokableMethod::invoke()
{}

void MInvokableMethod::invoke(void *arg1)
{
    M_UNUSED(arg1);
}

void MInvokableMethod::invoke(void *arg1, void* arg2)
{
    M_UNUSED(arg1);
    M_UNUSED(arg2);
}

void MInvokableMethod::invoke(void *arg1, void* arg2, void* arg3)
{
    M_UNUSED(arg1);
    M_UNUSED(arg2);
    M_UNUSED(arg3);
}
