#include "forward_list.h"

#ifndef STACK_H
#define STACK_H
namespace my {
    template<typename T>
    class stack {
    private:
        my::forward_list<T> list;
    public:
        void push(const T &el);

        void push(T &&el) noexcept;

        stack() = default;

        ~stack() = default;

        stack(const stack &el) { list = el.list;};

        stack(stack &&el) noexcept { list = el.list; };

        stack &operator=(const stack &el) {
            list = el.list;
            return *this;
        }

        stack &operator=(stack &&el) noexcept{
            list = std::move(el.list);
            return *this;
        }

        T get_first() {
            if(list.get_head() != nullptr){
                return list.get_head()->data;
            }
            throw empty_list_error();
        }

        T pop();

        size_t get_size() {
            return list.get_size();
        }

    };


}
template<typename T>
T my::stack<T>::pop() {
    T x;
    try {
        x = list.pop_front();
    }
    catch (empty_list_error &e) {
        throw e;
    }
    return x;
}

template<typename T>
void my::stack<T>::push(T &&el) noexcept {
    list.push_front(el);
}

template<typename T>
void my::stack<T>::push(const T &el) {
    list.push_front(el);
}
#endif //STACK_H


