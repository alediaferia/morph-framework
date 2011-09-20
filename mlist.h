#ifndef MLIST_H
#define MLIST_H

#include <iostream>
#include "mobject.h"

#include "mshareddataptr.h"

class MList;
class MListNode;

class MList : public MObject
{
    M_OBJECT(MList)
public:
    class ConstIterator;
    class Iterator;

    MList();
    MList( const MList &source );
    ~MList();
    //MList &operator=( const MList &right );

    MList::MRef init();

    mref& operator[](int index);
    void insert(int index, mref item );
    void append(mref item);
    mref pickAt(int index);
    void removeFirst();
    void removeLast();
    void removeAll(mref ele);
    void remove(mref ele);

    Iterator remove(const Iterator &it);
    ConstIterator remove(const ConstIterator &it);

    bool isEmpty() const;
    void print(std::ostream &out ) const;
    int size() const;
    void clear();
    mref get(int i) const;

    ConstIterator constBegin() const;
    ConstIterator constEnd() const;
    Iterator begin() const;
    Iterator end() const;

private:
    class MListPrivate;
    MListPrivate *d;
};

class MList::ConstIterator
{
public:
    ConstIterator();
    ConstIterator(const ConstIterator &copy);

    ConstIterator& operator++();
    ConstIterator& operator--();

    const mref& value() const;
    bool operator==(const ConstIterator& other) const;
    bool operator!= (const ConstIterator &other) const;

private:
    MListNode *currentNode;
    friend class MList;
};

class MList::Iterator
{
public:
    Iterator();
    Iterator(const Iterator &copy);

    Iterator& operator++();
    Iterator& operator--();

    mref& value();

    bool operator==(const Iterator& other) const;
    bool operator!= (const Iterator &other) const;

private:
    MListNode *currentNode;
    friend class MList;
};

#endif // MList
