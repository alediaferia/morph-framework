#include <iostream>

template <typename T>
class MList;

template <typename T>
class nodeClass
{
public:
    template<typename> friend class MList;
    nodeClass() {
        next = 0;
    }
private:
    T data;
    nodeClass *next;
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
    void removeFirst();
    void removeLast();
    void removeAll(T ele);
    void remove(T ele);
    bool isEmpty()const { return head == 0; }
    void print(std::ostream &out ) const;
    int size() const;
    void clear();
    T get(int i) const;
    void sort() ;
private:
    void free();
    nodeClass<T> *head;
    nodeClass<T> *tail;
};

template<typename T>
void MList<T>::sort() {
    nodeClass<T> *ptr1;
    nodeClass<T> *ptr2;
    nodeClass<T> *temp;
    nodeClass<T> *Imithead1;
    nodeClass<T> *Imithead2;
    nodeClass<T> *before;

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
            ptr2 = head;}
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
    nodeClass<T>*prec;
    nodeClass<T>*ptr;

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
    nodeClass<T>*prec;
    nodeClass<T>*ptr;

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
    nodeClass<T> *ptr = head;
    while ( ptr != 0 ){
        if(i==index){
            return ptr->data;
        }
        ptr = ptr -> next;
        index++;
    }
}

template <typename T>
const MList<T>& MList<T>::operator= ( const MList &right )
{
    if ( this == &right ) {
        return *this;
    }
    free();
    nodeClass<T> *ptr = right.head;
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
    nodeClass<T> *ptr = head;
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
    }else{
        i=i-1;
        int index = 0;
        nodeClass<T> *ptr = head;
        while ( ptr != 0 ){
            if(i==index){
                nodeClass<T> *tmp=new nodeClass<T>;
                tmp->data = item;
                tmp->next=ptr->next;
                ptr->next=tmp;
                return;
            }
            ptr = ptr -> next;
            index++;
        }
    }
}

template <typename T>
void MList<T>::append( const T &item )
{
    if (isEmpty()){
        nodeClass<T> *node = new nodeClass<T>;
        node->data = item;
        node->next = head;
        head = node;
        if ( tail == 0 ) { tail = node; }
        return;
    }
    nodeClass<T> *ptr = new nodeClass<T>;
    ptr -> data = item;
    tail -> next = ptr;
    tail = ptr;
}

template <typename T>
void MList<T>::removeFirst()
{
    if (!isEmpty() ) {
        nodeClass<T> *ptr = head;
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
            nodeClass<T> *ptr = head;
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
    nodeClass<T> *ptr = head;
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


