#include "mpair.h"

MPair::MPair() : MObject()
{
}

MPair::MPair(mref left, mref right) : MObject(),
    left(left),
    right(right)
{}

MPair::~MPair()
{}

MPair::MRef MPair::alloc(mref left, mref right)
{
    return MPair::MRef(new MPair(left, right));
}

/*template<typename V1, typename V2>
MPair<V1, V2>& MPair<V1, V2>::operator=(const MPair<V1, V2> &other)
{
    this->left = other.left;
    this->right = other.right;

    return *this;
}*/

