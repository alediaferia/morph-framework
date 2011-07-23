#ifndef MPAIR_H
#define MPAIR_H

template<typename V1, typename V2>
class MPair
{
public:
    MPair(const V1 &left, const V2 &right);
    ~MPair();

    V1& left;
    V2& right;

    MPair<V1, V2> operator=(const MPair<V1, V2> &other);
};

template<typename V1, typename V2>
MPair<V1, V2>::MPair(const V1 &left, const V2 &right) :
    left(left),
    right(right)
{}

template<typename V1, typename V2>
MPair<V1, V2>::~MPair()
{}

template<typename V1, typename V2>
MPair<V1, V2>& MPair<V1, V2>::operator=(const MPair<V1, V2> &other)
{
    this->left = other.left;
    this->right = other.right;

    return *this;
}

#endif // MPAIR_H
