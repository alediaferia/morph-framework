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
    ~MList();
     const MList &operator=( const MList &right );
    void appendToFirst( const T &item );
    void appendToLast( const T &item );
    void removeFirst();
    void removeLast();
    bool isEmpty()const { return head == NULL; }
    void print( ostream &out ) const;
    int size() const;
    void clear();
    T get(int i) const;

private:
    void free();
    nodeClass<T> *head, *tail;
};

template<class T>
 T MList<T>::get(int i) const{
    int index = 0;
    nodeClass<T> *ptr = head;
    while ( ptr != NULL )
    {
        if(i==index){
            return ptr->data;
        }
        ptr = ptr -> next;
        index++;
    }
}

 template <class T>
 const MList<T>& MList<T>::operator= ( const MList &right )
 {
     if ( this == &right ) { return *this; }
     free();
     nodeClass<T> *ptr = right.head;
     while ( ptr != NULL )
     {
        appendToFirst( ptr -> data);
         ptr = ptr -> next;
     }
     return *this;
 }



template<class T>
int MList<T>::size() const{
    int index = 0;
    nodeClass<T> *ptr = head;
    while ( ptr != NULL )
    {
        ptr = ptr -> next;
        index++;
    }

    return index;
}

template <class T>
std::ostream& operator<<( std::ostream&, const MList<T>&);


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
}

template <class T>
void MList<T>::appendToFirst( const T &item )
{
    nodeClass<T> *ptr = new nodeClass<T>;
    ptr->data = item;
    ptr->next = head;
    head = ptr;
    if ( tail == NULL ) { tail = ptr; }

}

template <class T>
void MList<T>::appendToLast( const T &item )
{
    if ( isEmpty() )
    {
        appendToFirst( item );
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
    if (!isEmpty() ) {
        nodeClass<T> *ptr = head;
        head = head -> next;
        delete ptr;
        if ( head == NULL )
        {
            tail = NULL;
        }
    }
}

template <class T>
void MList<T>::removeLast()
{
    if ( isEmpty() ) {
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
}

template <class T>
void MList<T>::free()
{
    while ( !isEmpty() ) { removeFirst(); }
}


template <class T>
void MList<T>::clear()
{
  free();
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

template <class T>
std::ostream& operator<<(std::ostream& os, const MList<T>& list) {
    list.print(os);
    return os;
}


