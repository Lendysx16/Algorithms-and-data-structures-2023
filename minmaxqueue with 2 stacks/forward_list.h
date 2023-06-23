#include <cstdlib>
#include <iostream>


#ifndef TASK2_FORWARD_LIST_H
#define TASK2_FORWARD_LIST_H

class empty_list_error : std::exception {
public:
    empty_list_error() = default;

    ~empty_list_error() override = default;

    const char *what() const noexcept override {
        return "List is empty";
    }
};


namespace my {
    template<typename T>
    class forward_list {
        struct node {
            T data;
            node *next = nullptr;
        };
        node *head;
        node *tail;
        size_t size;
    public:
        forward_list();

        forward_list(const forward_list &el);

        forward_list(forward_list &&el) noexcept;

        forward_list &operator=(forward_list &&el) noexcept;

        forward_list &operator=(const forward_list &el);

        void push_back(const T &el);

        void push_front(const T &el);

        void push_back(T &&el) noexcept;

        void push_front(T &&el) noexcept;

        T pop_front();

        T pop_back();
        node* get_head() const{
            return head;
        }

        void clear();

        ~forward_list();

        size_t get_size() {
            return size;
        }
    };

}

template<typename T>
my::forward_list<T>::forward_list() {
    head = nullptr;
    tail = nullptr;
    size = 0;
}


template<typename T>
void my::forward_list<T>::push_back(T &&el) noexcept {
    if (head == nullptr) {
        head = new node;
        head->data = el;
        tail = head;
        ++size;
        return;
    }
    tail->next = new node;
    tail = tail->next;
    tail->data = el;
    ++size;

}

template<typename T>
void my::forward_list<T>::push_back(const T &el) {
    if (head == nullptr) {
        head = new node;
        head->data = el;
        tail = head;
        size = 1;
        return;
    }
    tail->next = new node;
    tail = tail->next;
    tail->data = el;
    ++size;
}


template<typename T>
void my::forward_list<T>::push_front(const T &el) {
    if (head == nullptr) {
        head = new node;
        head->data = el;
        tail = head;
        size = 1;
        return;
    }
    node *tmp = new node;
    tmp->next = head;
    head = tmp;
    head->data = el;
    ++size;

}

template<typename T>
void my::forward_list<T>::push_front(T &&el) noexcept {
    if (head == nullptr) {
        head = new node;
        head->data = el;
        tail = head;
        ++size;
        return;
    }
    node *tmp = new node;
    tmp->next = head;
    head = tmp;
    head->data = el;
    ++size;
}


template<typename T>
my::forward_list<T>::~forward_list() {
    if (head == nullptr) { return; }
    node *current = head;
    node *next;
    while (current->next) {
        next = current->next;
        delete current;
        current = next;
    }
    delete current;
}


template<typename T>
my::forward_list<T>::forward_list(const forward_list<T> &el) {
    node *tmp = el.head;
    size = el.size;
    head = new node;
    head->data = tmp;
    tail = head;
    tmp = tmp->next;
    while (tmp != el.tail) {
        tail->next = new node;
        tail = tail->next;
        tail->data = tmp->data;
        tmp = tmp->next;
    }
    tail->next = new node;
    tail = tail->next;
    tail->data = tmp->data;
    tail->next = nullptr;
}

template<typename T>
my::forward_list<T>::forward_list(forward_list<T> &&el) noexcept {
    head = el.head;
    tail = el.tail;
    size = el.size;
    el.head = nullptr;
    el.tail = nullptr;
    el.size = 0;
}

template<typename T>
T my::forward_list<T>::pop_front() {
    if (head == nullptr || size == 0) { throw empty_list_error(); }
    --size;
    if (head == tail) {
        T x = head->data;
        delete head;
        head = nullptr;
        return x;
    }
    node *tmp = head->next;
    T x = head->data;
    delete head;
    head = tmp;
    return x;

}

template<typename T>
T my::forward_list<T>::pop_back() {
    if (head == nullptr || size == 0) { throw empty_list_error(); }
    if (head == tail) {
        T x = head->data;
        delete head;
        head = nullptr;
        return x;
    }
    --size;
    node *current = head;
    while (current->next != tail) {
        current = current->next;
    }
    T x = tail->data;
    delete tail;
    tail = current;
    tail->next = nullptr;
    return x;

}

template<typename T>
void my::forward_list<T>::clear() {
    if (head == nullptr) { return; }
    size = 0;
    node *current = head;
    node *next;
    while (current != tail) {
        next = current->next;
        delete current;
        current = next;
    }
    delete current;
    head = nullptr;
    tail = nullptr;
}

template<typename T>
my::forward_list<T> &my::forward_list<T>::operator=(forward_list<T> &&el) noexcept {
    if (this != &el) {
        head = el.head;
        tail = el.tail;
        size = el.size;
        el.head = nullptr;
        el.tail = nullptr;
        el.size = 0;
    }
    return *this;
}

template<typename T>
my::forward_list<T> &my::forward_list<T>::operator=(const forward_list<T> &el) {
    if (this != &el) {
        node *tmp = el.head;
        size = el.size;
        head = new node;
        head->data = tmp->data;
        tail = head;
        tmp = tmp->next;
        while (tmp != el.tail) {
            tail->next = new node;
            tail = tail->next;
            tail->data = tmp->data;
            tmp = tmp->next;
        }
        tail->next = new node;
        tail = tail->next;
        tail->data = tmp->data;
        tail->next = nullptr;
    }
    return *this;
}

#endif
