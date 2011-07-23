#include <iostream>

#include "mshareddataptr.h"

template <typename T>
class MList;

template <typename T>
class MListNode
{
public:
    template<typename> friend class MList;
    MListNode() :
        next(0)
    {}

    MListNode(const MListNode &copy) :
        data(copy.data),
        next(copy.next)
    {}

private:
    T data;
    MListNode *next;
};

template <typename T>
class MList
{
public:
    class ConstIterator;
    class Iterator;

    MList();
    MList( const MList &source );
    ~MList();
    MList &operator=( const MList &right );
    T& operator[](int index);
    void insert(int index, const T &item );
    void append( const T &item );
    T pickAt(int index);
    void removeFirst();
    void removeLast();
    void removeAll(T ele);
    void remove(T ele);
    Iterator remove(const Iterator &it);
    bool isEmpty()const { return d->size == 0; }
    void print(std::ostream &out ) const;
    int size() const;
    void clear();
    T get(int i) const;

    ConstIterator constBegin() const
    {
        ConstIterator it;
        it.currentNode = d->head;
        return it;
    }

    ConstIterator constEnd() const
    {
        return ConstIterator();
    }

    Iterator begin() const
    {
        Iterator it;
        it.currentNode = d->head;
        return it;
    }

    Iterator end() const
    {
        return Iterator();
    }

private:
    class MListPrivate;
    MSharedDataPtr<MListPrivate> d;
};

template<typename T>
class MList<T>::MListPrivate
{
public:
    MListPrivate(MList<T>* m)
        : m(m),
          head(0),
          tail(0),
          size(0)
    {}

    MListPrivate(const MListPrivate &copy) :
        m(m),
        size(copy.size)
    {
        if (!size) {
            head = 0;
            tail = 0;
            return;
        }

        head = new MListNode<T>(*copy.head);
        MListNode<T> *copyCurrent = copy.head;
        MListNode<T> *current = head;
        while (copyCurrent->next) {
            current->next = new MListNode<T>(*copyCurrent->next);
            copyCurrent = copyCurrent->next;
            current = current->next;
        }

        tail = copyCurrent;
    }

    ~MListPrivate()
    {
        free();
    }

    void free()
    {
        MListNode<T> *current = head;
        while (current->next) {
            MListNode<T> *tmp = current;
            current = current->next;
            delete tmp;
        }

        tail = 0;
        head = 0;
        size = 0;
    }

    MList<T> *m;
    MListNode<T> *head;
    MListNode<T> *tail;
    int size;
};

template<typename T>
MList<T>::MList() :
    d(new MListPrivate(this))
{}

template <class T>
MList<T>::MList( const MList &source ) :
    d(source.d)
{
}

template <typename T>
MList<T>::~MList()
{
}

template<typename T>
void MList<T>::removeAll(T ele){
    MListNode<T>*prec;
    MListNode<T>*ptr;

    ptr=d->head;
    if(d->head==0){
        return;
    }

    while (ptr!=NULL){
        if (ptr->data==ele){
            if (ptr==d->head){
                d->head=d->head->next;
                d->size--;
                delete ptr;
                ptr=d->head;
            }else{
                prec->next=ptr->next;
                d->size--;
                delete ptr;
                ptr=prec->next;
            }
        }else{
            prec=ptr;
            ptr=ptr->next;
        }
    }
}

template<typename T>
void MList<T>::remove(T ele){
    MListNode<T>*prec;
    MListNode<T>*ptr;

    ptr=d->head;
    if(d->head==0){
        return;
    }

    while (ptr!=NULL){
        if (ptr->data==ele){
            if (ptr==d->head){
                d->head=d->head->next;
                d->size--;
                delete ptr;
                ptr=d->head;
                return;
            }else{
                prec->next=ptr->next;
                d->size--;
                delete ptr;
                ptr=prec->next;
            }
        }else{
            prec=ptr;
            ptr=ptr->next;
        }
    }
}

template<typename T>
T MList<T>::get(int i) const
{
    int index = 0;
    MListNode<T> *ptr = d->head;
    while ( ptr != 0 ){
        if(i==index){
            return ptr->data;
        }
        ptr = ptr->next;
        index++;
    }

    return T();
}

template <typename T>
MList<T>& MList<T>::operator= ( const MList &right )
{
    d = right.d;
}

template<typename T>
T& MList<T>::operator[](int index)
{
    if (index >= d->size) {
        append(T());
        return d->tail->data;
    }

    if (index == d->size - 1) {
        return d->tail->data;
    }

    int i = 0;
    MListNode<T> *node = d->head;
    while (i < index) {
        node = node->next;
        i++;
    }

    return node->data;
}

template<typename T>
int MList<T>::size() const
{
    return d->size;
}

template <class T>
std::ostream& operator<<( std::ostream&, const MList<T>&);

template <typename T>
void MList<T>::insert(int i, const T &item )
{
    if (i >= d->size){
        append(item);
        return;
    }

    if (i == 0) { // prepending
        MListNode<T> *node = new MListNode<T>;
        node->data = item;
        node->next = d->head;
        d->head = node;
        d->size++;
        return;
    }

    int index = 0;
    MListNode<T> *ptr = d->head;
    while ( ptr != 0 ){
        if(i==index){
            MListNode<T> *tmp=new MListNode<T>;
            tmp->data = item;
            tmp->next=ptr->next;
            ptr->next=tmp;

            if (tmp->next == 0) {
                d->tail = tmp;
            }

            d->size++;
            return;
        }
        ptr = ptr->next;
        index++;
    }
}

template <typename T>
void MList<T>::append( const T &item )
{
    if (isEmpty()){
        MListNode<T> *node = new MListNode<T>;
        node->data = item;
        node->next = d->head;
        d->head = node;
        if ( d->tail == 0 ) { d->tail = node; }
        d->size++;
        return;
    }
    MListNode<T> *ptr = new MListNode<T>;
    ptr -> data = item;
    d->tail -> next = ptr;
    d->tail = ptr;
    d->size++;
}

template <typename T>
void MList<T>::removeFirst()
{
    if (isEmpty() ) {
        return;
    }
    MListNode<T> *ptr = d->head;
    d->head = d->head->next;
    delete ptr;
    if ( d->head == 0 ){
        d->tail = 0;
    }

    d->size--;
}

template <typename T>
void MList<T>::removeLast()
{
    if (isEmpty() ) {
        return;
    }

    if ( d->head == d->tail ) {
        removeFirst();
    }else{
        MListNode<T> *ptr = d->head;
        while ( ptr -> next -> next != 0) {
            ptr = ptr -> next;
        }
        delete d->tail;
        d->tail = ptr;
        d->tail -> next = 0;
    }

    d->size--;
}

template <typename T>
T MList<T>::pickAt(int index)
{
    int i = 0;
    MListNode<T> *node = d->head;
    MListNode<T> *previous = 0;
    do {
        if (!node) {
            break;
        }

        if (i == index) {
            if (!previous) {
                d->head = node->next;
            } else {
                previous->next = node->next;
            }
            T data = node->data;
            delete node;
            d->size--;
            return data;
        }

        previous = node;
        node = node->next;
        i++;
    } while (i <= index);

    return T();
}

template <typename T>
void MList<T>::clear()
{
    d->free();
}

template <typename T>
void MList<T>::print( std::ostream &out )const
{
    int i = 0;
    MListNode<T> *ptr = d->head;
    while ( ptr != 0 ){
        out << ptr -> data << std::endl;
        ptr = ptr -> next;
        i++;
    }
}

template<typename T>
class MList<T>::ConstIterator
{
public:
    ConstIterator() :
        currentNode(0)
    {}

    ConstIterator(const ConstIterator &copy) :
        currentNode(copy.currentNode)
    {}

    ConstIterator& operator++()
    {
        if (!currentNode) {
            return ConstIterator();
        }

        currentNode = currentNode->next;
        return *this;
    }

    const T& value() const
    {
        if (!currentNode) {
            return T();
        }

        return currentNode->data;
    }

    bool operator==(const ConstIterator& other) const
    {
        return currentNode == other.currentNode;
    }

    bool operator!= (const ConstIterator &other) const
    {
        return !operator==(other);
    }

private:
    MListNode<T> *currentNode;
    friend class MList<T>;
};

template<typename T>
class MList<T>::Iterator
{
public:
    Iterator() :
        currentNode(0)
    {}

    Iterator(const Iterator &copy) :
        currentNode(copy.currentNode)
    {}

    Iterator& operator++()
    {
        if (!currentNode) {
            return Iterator();
        }

        currentNode = currentNode->next;
        return *this;
    }

    T& value()
    {
        if (!currentNode) {
            return T();
        }

        return currentNode->data;
    }

    bool operator==(const Iterator& other) const
    {
        return currentNode == other.currentNode;
    }

    bool operator!= (const Iterator &other) const
    {
        return !operator==(other);
    }

private:
    MListNode<T> *currentNode;
    friend class MList<T>;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const MList<T>& list) {
    list.print(os);
    return os;
}


