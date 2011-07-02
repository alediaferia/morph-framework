#pragma once
#include <iostream>

using namespace std;

template <class T>
class MList;

template <class T>
class nodeClass
{
public:
    template<class> friend class MList;
    nodeClass() { next = NULL; }
private:
    T data;
    nodeClass *next;
};

template <class T>
class MList
{
public:
    MList() { head = tail = NULL; }
    MList( const MList &source );
    ~MList();  //Destructor
    const MList &operator=( const MList &right );
    void addItemToHead( const T &item );
    void addItemToTail( const T &item );
    void removeFirst();
    void removeLast();
    bool isFull()const { return false; }
    bool isEmpty()const { return head == NULL; }
    void print( ostream &out ) const;
    void addItemInOrder( T &item );

private:
    void free();
    nodeClass<T> *head, *tail;
    int count;
};

template <class T>
const MList<T>& MList<T>::operator= ( const MList &right )
{
    if ( this == &right ) { return *this; }
    free();
    nodeClass<T> *ptr = right.head;
    while ( ptr != NULL )
    {
        addItemInOrder( ptr -> data );
        ptr = ptr -> next;
    }
    return *this;
}

template <class T>
MList<T>::MList( const MList &source )
{
    head = tail = NULL;
    *this = source;
}


template <class T>
MList<T>::~MList()
{
    free();
    count=0;
}

template <class T>
void MList<T>::addItemToHead( const T &item )
{
    nodeClass<T> *ptr = new nodeClass<T>;
    ptr->data = item;
    ptr->next = head;
    head = ptr;
    if ( tail == NULL ) { tail = ptr; }
    count++;
}

template <class T>
void MList<T>::addItemToTail( const T &item )
{
    if ( isEmpty() )
    {
        addItemToHead( item );
        return;
    }
    nodeClass<T> *ptr = new nodeClass<T>;
    ptr -> data = item;
    tail -> next = ptr;
    tail = ptr;
}

template <class T>
void MList<T>::removeFirst()
{
    if ( isEmpty() ) { cerr<<"empty list\n"; exit(41); }
    nodeClass<T> *ptr = head;
    head = head -> next;
    delete ptr;
    if ( head == NULL ) { tail = NULL; }
}

template <class T>
void MList<T>::removeLast()
{
    if ( isEmpty() ) { cerr<<"empty list\n"; exit(41); }
    if ( head == tail ) { removeFirst(); }
    else
    {
        nodeClass<T> *ptr = head;
        while ( ptr -> next -> next != NULL) { ptr = ptr -> next; }
        delete tail;
        tail = ptr;
        tail -> next = NULL;
    }
}

template <class T>
void MList<T>::free()
{
    while ( !isEmpty() ) { removeFirst(); }
}


template <class T>
void MList<T>::print( ostream &out )const
{
    int i = 0;
    nodeClass<T> *ptr = head;
    while ( ptr != NULL )
    {
        out << ptr -> data << endl;
        ptr = ptr -> next;
        i++;
    }
}

