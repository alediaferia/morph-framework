#include "mlist.h"

class MListNode
{
public:
    friend class MList;
    MListNode() :
        next(0),
        previous(0)
    {}

    MListNode(const MListNode &copy) :
        data(copy.data),
        next(copy.next)
    {}

private:
    mref data;
    MListNode *next;
    MListNode *previous;
};


// ConstIterator

MList::ConstIterator::ConstIterator() :
    currentNode(0)
{}

MList::ConstIterator::ConstIterator(const ConstIterator &copy) :
    currentNode(copy.currentNode)
{}

MList::ConstIterator& MList::ConstIterator::operator++()
{
    if (!currentNode) {
        return *this;
    }

    currentNode = currentNode->next;
    return *this;
}

MList::ConstIterator& MList::ConstIterator::operator--()
{
    if (!currentNode) {
        return *this;
    }

    currentNode = currentNode->previous;
    return *this;
}

const mref& MList::ConstIterator::value() const
{
    return currentNode->data;
}

bool MList::ConstIterator::operator==(const ConstIterator& other) const
{
    return currentNode == other.currentNode;
}

bool MList::ConstIterator::operator!= (const ConstIterator &other) const
{
    return !operator==(other);
}

// end of ConstIterator

// Iterator
MList::Iterator::Iterator() :
    currentNode(0)
{}

MList::Iterator::Iterator(const Iterator &copy) :
    currentNode(copy.currentNode)
{}

MList::Iterator& MList::Iterator::operator++()
{
    if (!currentNode) {
        return *this;
    }

    currentNode = currentNode->next;
    return *this;
}

MList::Iterator& MList::Iterator::operator--()
{
    if (!currentNode) {
        return *this;
    }

    currentNode = currentNode->previous;
    return *this;
}

mref& MList::Iterator::value()
{
    return currentNode->data;
}

bool MList::Iterator::operator==(const Iterator& other) const
{
    return currentNode == other.currentNode;
}

bool MList::Iterator::operator!= (const Iterator &other) const
{
    return !operator==(other);
}

// end of Iterator


// MListPrivate
class MList::MListPrivate
{
public:
    MListPrivate(MList* m)
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

        head = new MListNode(*copy.head);
        MListNode *copyCurrent = copy.head;
        MListNode *current = head;
        while (copyCurrent->next) {
            current->next = new MListNode(*copyCurrent->next);
            copyCurrent = copyCurrent->next;
            MListNode *previous = current;
            current = current->next;
            current->previous = previous;
        }

        tail = copyCurrent;
    }

    ~MListPrivate()
    {
        free();
    }

    void free()
    {
        if (!head) {
            return;
        }
        MListNode *current = head;
        while (current->next) {
            MListNode *tmp = current;
            current = current->next;
            delete tmp;
        }

        tail = 0;
        head = 0;
        size = 0;
    }

    MList *m;
    MListNode *head;
    MListNode *tail;
    int size;
};

// end of MListPrivate

MList::MList() :
    d(new MListPrivate(this))
{}

MList::MList( const MList &source ) :
    d(source.d)
{
}

MList::~MList()
{
    delete d;
}

void MList::removeAll(mref ele){
    MListNode *ptr;
    ptr=d->head;

    while (ptr){
        if (ptr->data == ele){
            if (ptr == d->head){
                d->head=ptr->next;
                d->size--;
                delete ptr;
                ptr=d->head;
                ptr->previous = 0;
            }else{
                ptr->previous->next=ptr->next;
                d->size--;
                MListNode *tmp = ptr;
                ptr=ptr->next;
                delete tmp;
            }
        }else{
            ptr=ptr->next;
        }
    }
}

void MList::remove(mref ele){
    MListNode *ptr;

    ptr=d->head;
    while (ptr){
        if (ptr->data==ele){
            if (ptr==d->head){
                d->head=ptr->next;
                d->size--;
                delete ptr;
                return;
            }else{
                ptr->previous->next=ptr->next;
                d->size--;
                delete ptr;
                return;
            }
        }else{
            ptr=ptr->next;
        }
    }
}

mref MList::get(int i) const
{
    int index = 0;
    MListNode *ptr = d->head;
    while ( ptr != 0 ){
        if(i==index){
            return ptr->data;
        }
        ptr = ptr->next;
        index++;
    }

    return mref();
}

/*MList<T>& MList<T>::operator= ( const MList &right )
{
    d = right.d;
}*/

mref& MList::operator[](int index)
{
    if (index >= d->size) {
        append(mref());
        return d->tail->data;
    }

    if (index == d->size - 1) {
        return d->tail->data;
    }

    int i = 0;
    MListNode *node = d->head;
    while (i < index) {
        node = node->next;
        i++;
    }

    return node->data;
}

int MList::size() const
{
    return d->size;
}

std::ostream& operator<<( std::ostream&, const MList&);

void MList::insert(int i, mref item )
{
    if (i >= d->size){
        append(item);
        return;
    }

    if (i == 0) { // prepending
        MListNode *node = new MListNode;
        node->data = item;
        node->next = d->head;
        d->head = node;
        d->size++;
        return;
    }

    int index = 0;
    MListNode *ptr = d->head;
    while ( ptr != 0 ){
        if(i==index){
            MListNode *tmp=new MListNode;
            tmp->data = item;
            tmp->next=ptr->next;
            tmp->previous = ptr;
            ptr->next=tmp;

            if (tmp->next == 0) {
                d->tail = tmp;
            } else {
                tmp->next->previous = tmp;
            }

            d->size++;
            return;
        }
        ptr = ptr->next;
        index++;
    }
}

void MList::append(mref item)
{
    if (isEmpty()){
        MListNode *node = new MListNode();
        node->data = item;
        node->next = d->head;
        d->head = node;
        if ( d->tail == 0 ) { d->tail = node; }
        d->size++;
        return;
    }

    MListNode *ptr = new MListNode;
    ptr -> data = item;
    d->tail->next = ptr;
    ptr->previous = d->tail;
    d->tail = ptr;
    d->size++;
}

void MList::removeFirst()
{
    if (isEmpty() ) {
        return;
    }
    MListNode *ptr = d->head;
    d->head = d->head->next;
    d->head->previous = 0;
    delete ptr;
    if ( d->head == 0 ) {
        d->tail = 0;
    }

    d->size--;
}

void MList::removeLast()
{
    if (isEmpty() ) {
        return;
    }

    if ( d->head == d->tail ) {
        removeFirst();
    } else {
        MListNode *node = d->tail;
        d->tail = d->tail->previous;
        delete node;
        d->tail->next = 0;
    }

    d->size--;
}

mref MList::pickAt(int index)
{
    int i = 0;
    MListNode *node = d->head;
    do {
        if (!node) {
            break;
        }

        if (i == index) {
            if (!node->previous) {
                d->head = node->next;
            } else {
                node->next->previous = node->previous;
                node->previous->next = node->next;
            }
            mref data = node->data;
            delete node;
            d->size--;
            return data;
        }
        node = node->next;
        i++;
    } while (i <= index);

    return mref();
}

void MList::clear()
{
    d->free();
}

bool MList::isEmpty() const
{
    return d->size == 0;
}

void MList::print( std::ostream &out )const
{
    /*int i = 0;
    MListNode *ptr = d->head;
    while ( ptr != 0 ){
        out << ptr -> data << std::endl;
        ptr = ptr -> next;
        i++;
    }*/
}

std::ostream& operator<<(std::ostream& os, const MList& list)
{
    /*list.print(os);
    return os;*/
}

MList::Iterator MList::remove(const Iterator &it)
{
    MListNode *node = it.currentNode;
    node->previous->next = node->next;

    Iterator resultIt;
    resultIt.currentNode = node->previous;
    delete node;

    return resultIt;
}

MList::ConstIterator MList::remove(const ConstIterator &it)
{
    MListNode *node = it.currentNode;
    node->previous->next = node->next;

    ConstIterator resultIt;
    resultIt.currentNode = node->previous;
    delete node;

    return resultIt;
}

MList::ConstIterator MList::constBegin() const
{
    ConstIterator it;
    it.currentNode = d->head;
    return it;
}

MList::ConstIterator MList::constEnd() const
{
    return ConstIterator();
}

MList::Iterator MList::begin() const
{
    Iterator it;
    it.currentNode = d->head;
    return it;
}

MList::Iterator MList::end() const
{
    return Iterator();
}
