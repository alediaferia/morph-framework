#include "minvokablemethod.h"
#include "mobject_macros.h"

void MInvokableMethod::invoke()
{}

void MInvokableMethod::invoke(mref ref)
{
    M_UNUSED(ref);
}

void MInvokableMethod::invoke(mref ref1, mref ref2)
{
    M_UNUSED(ref1);
    M_UNUSED(ref2);
}

void MInvokableMethod::invoke(mref ref1, mref ref2, mref ref3)
{
    M_UNUSED(ref1);
    M_UNUSED(ref2);
    M_UNUSED(ref3);
}
