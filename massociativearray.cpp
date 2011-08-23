#include "massociativearray.h"


class MAssociativeArray::MAssociativeArrayPrivate
{
public:
    MAssociativeArrayPrivate(MAssociativeArray *m)
        : m(m),
          values(MList::alloc())
    {}

    MAssociativeArrayPrivate(const MAssociativeArrayPrivate& copy)
        : m(copy.m),
          values(copy.values)
    {}

    MAssociativeArray *m;
    MList::MRef values;
};


MAssociativeArray::MAssociativeArray() : MObject(),
    d(new MAssociativeArrayPrivate(this))
{
}


MAssociativeArray::MAssociativeArray(const MAssociativeArray& copy) : MObject(),
    d(new MAssociativeArrayPrivate(*copy.d))
{}


MAssociativeArray::~MAssociativeArray()
{}


int MAssociativeArray::size() const
{
    return d->values->size();
}


bool MAssociativeArray::hasKey(mref key) const
{
    MList::ConstIterator it = d->values->constBegin();
    for (; it != d->values->constEnd(); ++it) {
        MPair::MRef pair = it.value();
        if (pair->left == key) {
            return true;
        }
    }
    return false;
}


void MAssociativeArray::insert(mref key, mref value)
{
    d->values->append(MPair::alloc(key, value));
}

mref& MAssociativeArray::operator[](mref key)
{
    MList::Iterator it = d->values->begin();

    for (; it != d->values->end(); ++it) {
        MPair::MRef pair = it.value();
        if (pair->left == key) {
            return pair->right;
        }
    }

    d->values->append(MPair::alloc(key, mref()));
    MPair::MRef &pair = (MPair::MRef&)d->values->operator [](d->values->size() - 1);
    return pair->right;
}


mref MAssociativeArray::value(mref key) const
{
    MList::ConstIterator it = d->values->constBegin();
    for (; it != d->values->constEnd(); ++it) {
        MPair::MRef item = it.value();
        if (item->left == key) {
            return item->right;
        }
    }

    return mref();
}


MList::MRef MAssociativeArray::values(mref key) const
{
    MList::MRef list = MList::alloc();
    MList::ConstIterator it = d->values->constBegin();
    for (; it != d->values->constEnd(); ++it) {
        MPair::MRef pair = it.value();
        if (pair->left == key) {
            list->append(pair->right);
        }
    }
    return list;
}


mref MAssociativeArray::pick(mref key)
{
    MList::ConstIterator it = d->values->constBegin();
    for (; it != d->values->constEnd(); ++it) {
        MPair::MRef pair = it.value();
        if (pair->left == key) {
            mref data = pair->right;
            d->values->remove(it);
            return data;
        }
    }

    return mref();
}


MList::MRef MAssociativeArray::pickAll(mref key)
{
    MList::MRef list = MList::alloc();

    MList::ConstIterator it = d->values->constBegin();
    for (; it != d->values->constEnd(); ++it) {
        MPair::MRef pair = it.value();
        if (pair->left == key) {
            mref data = pair->right;
            it = d->values->remove(it);
            list->append(data);
        }
    }

    return list;
}


MList::MRef MAssociativeArray::values() const
{
    MList::MRef list = MList::alloc();

    MList::ConstIterator it = d->values->constBegin();
    for (; it != d->values->constEnd(); ++it) {
        MPair::MRef pair = it.value();
        list->append(pair->right);
    }

    return list;
}

