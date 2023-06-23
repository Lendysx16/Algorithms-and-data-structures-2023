
#ifndef MY_VECTOR_H
#define MY_VECTOR_H

#include <iostream>
#include "sort.h"

namespace my {
    template<typename T>
    class vector {
    private:
        size_t len = 0;
        size_t capacity = 0;
        T *arr = nullptr;

        void resize();

    public:
        vector();

        vector(size_t len);

        vector &operator=(const vector &el);
        vector &operator=(vector && el) noexcept;
        vector(const vector &el);

        vector(vector &&el) noexcept;

        ~vector();

        size_t get_size() { return len; };

        void append(T &&el) noexcept;

        void append(const T &el);

        void pop() { len = len == 0 ? 0 : len - 1; }

        T &operator[](size_t i);
        void sort(){
            my::mergesort(this->arr, this->len);
        }
    };


}

template<typename T>
my::vector<T>::vector() {
    delete arr;
    arr = new T[10];
    capacity = 10;
    len = 0;
}

template<typename T>
my::vector<T>::vector(size_t len_) {
    delete arr;
    capacity = len_ < 10 ? 10 : len_;
    arr = new T[capacity];
    len = 0;
}

template<typename T>
my::vector<T>::~vector() {
    delete[] arr;
}

template<typename T>
void my::vector<T>::append(T &&el) noexcept {
    if (len == capacity) {
        resize();
    }
    arr[len] = std::move(el);
    ++len;
}

template<typename T>
void my::vector<T>::append(const T &el) {
    if (len == capacity - 1) {
        resize();
    }
    arr[len] = el;
    ++len;
}

template<typename T>
void my::vector<T>::resize() {
    T *tmp = new T[capacity * 2];
    capacity *= 2;
    for (size_t i = 0; i < len; ++i) {
        tmp[i] = std::move(arr[i]);
    }
    T *tmp_2 = arr;
    arr = tmp;
    tmp = nullptr;
    delete[] tmp_2;
}

template<typename T>
T &my::vector<T>::operator[](size_t i) {
    if (i < len) {
        return arr[i];
    }
    throw std::out_of_range("Out of range");
}

template<typename T>
my::vector<T>::vector(const my::vector<T> &el) {
    this->len = el.len;
    this->capacity = el.capacity;
    delete this->arr;
    this->arr = new T[capacity];
    for (size_t i = 0; i < len; ++i) {
        this->arr[i] = el.arr[i];
    }
}

template<typename T>
my::vector<T>::vector( my::vector<T> &&el) noexcept {
    delete this->arr;
    this->arr = el.arr;
    el.arr = nullptr;
    this->len = len;
    this->capacity = capacity;
}

template<typename T>
my::vector<T> &my::vector<T>::operator=(const my::vector<T> &el) {
    if(this != &el){
        this->len = el.len;
        this->capacity = el.capacity;
        delete this->arr;
        this->arr = new T[capacity];
        for (size_t i = 0; i < len; ++i) {
            this->arr[i] = el.arr[i];
        }
    }
    return *this;
}
template<typename T>
my::vector<T> &my::vector<T>::operator=(my::vector<T> &&el) noexcept{
    if(this != &el){
        delete this->arr;
        this->arr = el.arr;
        el.arr = nullptr;
        this->len = len;
        this->capacity = capacity;
    }
    return *this;
}

#endif
