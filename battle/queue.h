
#include "forward_list.h"
#ifndef TASK2_QUEUE_H
#define TASK2_QUEUE_H

namespace my {
    template <typename T>
    class queue {
    private:
        forward_list<T> list;
    public:
        queue() = default;
        ~queue() = default;
        queue(const queue&el);
        queue(queue &&el) noexcept;
        queue &operator=(const queue& el) {list = el.list;};
        queue &operator=(queue && el) noexcept {list = el.list;};
        void push(const T&el);
        void push(T&&el) noexcept;
        T pop();
        size_t get_size(){
            return list.get_size();
        }
    };

}
template <typename T>
my::queue<T>::queue(const queue& el) {
    list = el.list;
}

template <typename T>
my::queue<T>::queue( queue&& el) noexcept{
    list = std::move(el.list);
}

template <typename T>
T my::queue<T>::pop() {
    T x;
    try{
        x = list.pop_front();
    }
    catch (empty_list_error &e){
        throw e;
    }
    return x;
}

template <typename T>
void my::queue<T>::push(T && el) noexcept{
    list.push_back(el);
}

template <typename T>
void my::queue<T>::push(const T & el){
    list.push_back(el);
}

#endif //TASK2_QUEUE_H


