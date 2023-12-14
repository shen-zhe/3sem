
template<typename T>
// Определение структуры для узла списка
struct Node {
    T data;
    Node<T> *next;
    Node<T> *prev;
    //копирование написать 
    
    Node(T value);
};

template<typename T>
class DoublyLinkedList {
private:
    Node<T>* head;
    Node<T>* tail;

public:
    DoublyLinkedList();
    DoublyLinkedList(const DoublyLinkedList& other);
    DoublyLinkedList(const DoublyLinkedList& list1, const DoublyLinkedList& list2);

    void clear();
    void clone(const DoublyLinkedList& other);

    Node<T>* push_front(T data);
    Node<T>* push_back(T data);
    Node<T>* pop_front();
    Node<T>* pop_back();
    void traverseForward();
    void traverseBackward();

    bool empty() const {
        return head == nullptr;
    }
    
    Node<T>* get_N_i(int index);
    Node<T>* operator [] (int index);
    void forEach(const DoublyLinkedList<T>& other, void(*operation) (T&, const T&));
    Node<T>* insert(size_t index, T data);
    DoublyLinkedList operator=( const DoublyLinkedList & other);
    void erase(size_t index);


    class Iterator {
    private:
        Node<T>* current;

    public:
        Iterator(Node<T>* start) : current(start) {}

        // Переход к следующему элементу
        Iterator& operator++() {
            current = current->next;
            return *this;
        }

        // Проверка на равенство итераторов
        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }

        // Получение значения текущего элемента
        T& operator*() const {
            return current->data;
        }
    };

    Iterator begin() const {
        return Iterator(head);
    }
    Iterator end() const {
        return Iterator(nullptr);
    }

    bool contains(T data) const;
    Node<T>* find(T data) const;
    Node<T>* getHead() const {
        return head;
    }

    Node<T>* getTail() const {
        return tail;
    }

    void remove(const T& value) {
        Node<T>* current = head;

        // Поиск узла с заданным значением
        while (current != nullptr && current->data != value) {
            current = current->next;
        }

        // Если узел с найденным значением был найден, производим удаление
        if (current != nullptr) {
            // Обновляем указатели next и prev у соседних узлов
            if (current->prev != nullptr) {
                current->prev->next = current->next;
            } else {
                // Если удаляемый элемент - первый, обновляем указатель head
                head = current->next;
            }

            if (current->next != nullptr) {
                current->next->prev = current->prev;
            } else {
                // Если удаляемый элемент - последний, обновляем указатель tail
                tail = current->prev;
            }

            // Удаляем узел и освобождаем память
            delete current;
        }
    }
    // + - объединение
    // итератор обхода 
    // список списков через шаблоны 
    // Деструктор для освобождения памяти, выделенной под узлы
    ~DoublyLinkedList();
};

template<typename T>
Node<T>::Node(T value) : data(value), next(nullptr), prev(nullptr) {}


template<typename T>
DoublyLinkedList<T>::DoublyLinkedList() : head(nullptr), tail(nullptr) {}

// добавления элемента в конец списка
template<typename T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList& other) : head(nullptr), tail(nullptr) {
    Node<T>* current = other.head;
    clear();
    while (current != nullptr) {
        push_back(current->data);
        current = current->next;
    }
}


template<typename T>
void DoublyLinkedList<T>::clone(const DoublyLinkedList& other){
    Node<T>* current = other.head;
    clear();
    while (current != nullptr) {
        push_back(current->data);
        current = current->next;
    }
}

template<typename T>
bool DoublyLinkedList<T>::contains(T data) const {
        Node<T>* current = head;
        while (current != nullptr) {
            if (current->data == data) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

template<typename T>
Node<T>* DoublyLinkedList<T>::find(T data) const {
        Node<T>* current = head;
        while (current != nullptr) {
            if (current->data == data) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }





template<typename T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList& list1, const DoublyLinkedList& list2) : head(nullptr), tail(nullptr) {
    Node<T>* currentList1 = list1.head;
    while (currentList1 != nullptr) {
        push_back(currentList1->data);
        currentList1 = currentList1->next;
    }

    Node<T>* currentList2 = list2.head;
    while (currentList2 != nullptr) {
        push_back(currentList2->data);
        currentList2 = currentList2->next;
    }
}

template<typename T>
Node<T>* DoublyLinkedList<T>::push_front(T data){
    Node<T>* ptr = new Node<T>(data);

    ptr -> next = head;
    if(head != NULL){
        head -> prev = ptr;
    }
    if(tail == NULL){
        tail = ptr;
    }
    head = ptr;
    return ptr;
}

template<typename T>
Node<T>* DoublyLinkedList<T>:: push_back(T data){
    Node<T>* ptr = new Node<T>(data);

    ptr -> prev = tail;
    if(head != NULL){
        tail -> next = ptr;
    }
    if(tail == NULL){
        head = ptr;
    }
    tail = ptr;
    return ptr;
}

template<typename T>
Node<T>* DoublyLinkedList<T>::pop_front(){
    if(head == NULL){
        return NULL;
    }

    Node<T>* ptr = head -> next;
    if(ptr != NULL){
            ptr -> prev = NULL;
    } else {
        tail = NULL;
    }
    delete head;
    head = ptr;
    return head;
}

template<typename T>
Node<T>* DoublyLinkedList<T>::pop_back(){
    if(tail == NULL){
        return NULL;
    }

    Node<T>* ptr = tail -> next;
    if(ptr != NULL){
            ptr -> next = NULL;
    } else {
        head = NULL;
    }
    delete tail;
    tail = ptr;
    return tail;
}
// перебор элементов списка в прямом направлении
template<typename T>
void DoublyLinkedList<T>::traverseForward() {
    for(Node<T>* ptr = head; ptr != nullptr; ptr = ptr -> next){
        cout << ptr->data << " ";
    }
    cout << endl;
}

// перебор элементов списка в обратном направлении
template<typename T>
void DoublyLinkedList<T>::traverseBackward() {
    for(Node<T>* ptr = tail; ptr != nullptr; ptr = ptr -> prev){
        cout << ptr->data << " ";
    }
    cout << endl;
}

// получение i-ого элемента
template<typename T>
Node<T>* DoublyLinkedList<T>::get_N_i(int index){
    Node<T>* ptr = head;
    int n = 0;

    while (n != index) {
            if (ptr == NULL)
                return ptr;
            ptr = ptr->next;
            n++;
    }

    return ptr;
}
template<typename T>
Node<T>* DoublyLinkedList<T>::operator [] (int index){
    return get_N_i(index);
}



template<typename T>
void DoublyLinkedList<T>::forEach(const DoublyLinkedList<T>& other, void(*operation) (T&, const T&/*сюда список запихать*/)) {
    Node<T>* current1 = head;
    Node<T>* current2 = other.head;

    while (current1 != nullptr && current2 != nullptr) {
        operation(current1->data, current2->data);
        current1 = current1->next;
        current2 = current2->next;
    }
}

template<typename T>
Node<T>* DoublyLinkedList<T>::insert(size_t index, T data){
    Node<T>* right = get_N_i(index);
    if(right == NULL){
        return push_back(data);
    }
    Node<T>* left = right -> prev;
    if(left == NULL){
        return push_front(data);
    }

    Node<T>* ptr = new Node<T>(data);
    ptr -> prev = left;
    ptr -> next = right;
    left -> next = ptr;
    right -> prev = ptr;

    return ptr;
}

template<typename T>
DoublyLinkedList<T> DoublyLinkedList<T> :: operator=( const DoublyLinkedList & other){
    
    clone(other);
    return *this;
}

template<typename T>
void DoublyLinkedList<T>::erase(size_t index){
    
    Node<T>* ptr = get_N_i(index);
    if(ptr == NULL) {
        return;
    }
    if(ptr -> prev == NULL){
        pop_front();
        return;
    }
    if (ptr -> next == NULL){
        pop_back();
        return;
    }
    Node<T>* left = ptr -> prev;
    Node<T>* right =ptr -> next;
    left -> next = right;
    right -> prev = left;

    delete ptr;
}

template<typename T>
void DoublyLinkedList<T>::clear(){
    Node<T>* current = head;
    while (current != nullptr) {
        Node<T>* next = current->next;
        delete current;
        current = next;
    }
};

// Деструктор для освобождения памяти, выделенной под узлы
template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    clear();
}

//лямбда функции в 3 задаче 