#include <iostream>

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
private:
    T data;
    MListNode *next;
};

template <typename T>
class MList
{
public:
    MList() { head = tail = 0; }
    MList( const MList &source );
    ~MList();
    const MList &operator=( const MList &right );
    void insert(int index, const T &item );
    void append( const T &item );
    T pickAt(int index);
    void removeFirst();
    void removeLast();
    void removeAll(T ele);
    void remove(T ele);
    bool isEmpty()const { return head == 0; }
    void print(std::ostream &out ) const;
    int size() const;
    void clear();
    T get(int i) const;
    void sort();
private:
    void free();
    MListNode<T> *head;
    MListNode<T> *tail;
};

template<typename T>
void MList<T>::sort() {
    MListNode<T> *ptr1;
    MListNode<T> *ptr2;
    MListNode<T> *temp;
    MListNode<T> *Imithead1;
    MListNode<T> *Imithead2;
    MListNode<T> *before;

    if (head != 0) {
        ptr2 = head;
        ptr1 = head->next;

        while(ptr1 != 0 ) {
            if (ptr2->data > ptr1->data ) {
                temp = ptr2;
                while(temp->next != ptr1){
                    temp = temp->next;
                }
                temp->next = ptr1->next;
                ptr1->next = ptr2;
                head = ptr1;
            }
            ptr1 = ptr1->next;
            ptr2 = head;
        }
        before = head;
        Imithead1 = Imithead2 = head->next;

        while (Imithead1 != 0) {
            while (Imithead2 != 0 ) {
                ptr1 = ptr2 =Imithead2;
                while(ptr1 != 0 ) {
                    if (ptr2->data > ptr1->data ) {
                        temp = ptr2;
                        while(temp->next != ptr1){
                            temp = temp->next;
                        }
                        before->next = ptr1;
                        temp->next = ptr1->next;
                        ptr1->next = ptr2;
                        Imithead2 = ptr1;
                    }
                    ptr1 = ptr1->next;
                    ptr2 = Imithead2;
                }
                before = Imithead2;
                Imithead2 = Imithead2->next;
            }
            Imithead1 = Imithead1->next;
            Imithead2 = Imithead1;
        }
    }
}

template<typename T>
void MList<T>::removeAll(T ele){
    MListNode<T>*prec;
    MListNode<T>*ptr;

    ptr=head;
    if(head==0){
        return;
    }

    while (ptr!=NULL){
        if (ptr->data==ele){
            if (ptr==head){
                head=head->next;
                delete ptr;
                ptr=head;
            }else{
                prec->next=ptr->next;
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

    ptr=head;
    if(head==0){
        return;
    }

    while (ptr!=NULL){
        if (ptr->data==ele){
            if (ptr==head){
                head=head->next;
                delete ptr;
                ptr=head;
                return;
            }else{
                prec->next=ptr->next;
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
T MList<T>::get(int i) const{
    int index = 0;
    MListNode<T> *ptr = head;
    while ( ptr != 0 ){
        if(i==index){
            return ptr->data;
        }
        ptr = ptr -> next;
        index++;
    }

    return T();
}

template <typename T>
const MList<T>& MList<T>::operator= ( const MList &right )
{
    if ( this == &right ) {
        return *this;
    }
    free();
    MListNode<T> *ptr = right.head;
    while ( ptr != 0 ) {
        append( ptr -> data);
        ptr = ptr -> next;
    }
    return *this;
}

template<typename T>
int MList<T>::size() const
{
    int index = 0;
    MListNode<T> *ptr = head;
    while ( ptr != 0 ){
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
    head = tail = 0;
    *this = source;
}


template <typename T>
MList<T>::~MList()
{
    free();
}

template <typename T>
void MList<T>::insert(int i, const T &item )
{
    if(i>=this->size()){
        append(item);
        return;
    }

    if (i == 0) { // prepending
        MListNode<T> *node = new MListNode<T>;
        node->data = item;
        node->next = head;
        head = node;
        return;
    }

    int index = 0;
    MListNode<T> *ptr = head;
    while ( ptr != 0 ){
        if(i==index){
            MListNode<T> *tmp=new MListNode<T>;
            tmp->data = item;
            tmp->next=ptr->next;
            ptr->next=tmp;

            if (tmp->next == 0) {
                tail = tmp;
            }

            return;
        }
        ptr = ptr -> next;
        index++;
    }
}

template <typename T>
void MList<T>::append( const T &item )
{
    if (isEmpty()){
        MListNode<T> *node = new MListNode<T>;
        node->data = item;
        node->next = head;
        head = node;
        if ( tail == 0 ) { tail = node; }
        return;
    }
    MListNode<T> *ptr = new MListNode<T>;
    ptr -> data = item;
    tail -> next = ptr;
    tail = ptr;
}

template <typename T>
void MList<T>::removeFirst()
{
    if (!isEmpty() ) {
        MListNode<T> *ptr = head;
        head = head -> next;
        delete ptr;
        if ( head == 0 ){
            tail = 0;
        }
    }
}

template <typename T>
void MList<T>::removeLast()
{
    if (!isEmpty() ) {
        if ( head == tail ) {
            removeFirst();
        }else{
            MListNode<T> *ptr = head;
            while ( ptr -> next -> next != 0) {
                ptr = ptr -> next;
            }
            delete tail;
            tail = ptr;
            tail -> next = 0;
        }
    }
}

template <typename T>
T MList<T>::pickAt(int index)
{
    int i = 0;
    MListNode<T> *node = head;
    MListNode<T> *previous = 0;
    do {
        if (!node) {
            break;
        }

        if (i == index) {
            if (!previous) {
                head = node->next;

            } else {
                previous->next = node->next;
            }
            T data = node->data;
            delete node;
            return data;
        }

        previous = node;
        node = node->next;
        i++;
    } while (i <= index);

    return T();
}

template <typename T>
void MList<T>::free()
{
    while ( !isEmpty() ) { removeFirst(); }
}


template <typename T>
void MList<T>::clear()
{
    free();
}

template <typename T>
void MList<T>::print( std::ostream &out )const
{
    int i = 0;
    MListNode<T> *ptr = head;
    while ( ptr != 0 ){
        out << ptr -> data << std::endl;
        ptr = ptr -> next;
        i++;
    }
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const MList<T>& list) {
    list.print(os);
    return os;
}


