#include "stack.h"

#ifndef QUEUE_MINMAX_H
#define QUEUE_MINMAX_H

namespace my {


    template<typename T>
    class double_stack_queue {
    private:
        T left_min;
        T left_max;

        struct elem {
            T element;
            T min;
            T max;
            elem() = default;
            elem(T el, T mn, T mx) : element(el), min(mn), max(mx) {};
        };


        stack<T> left_stack;
        stack<elem> right_stack;
    public:
        double_stack_queue() = default;

        double_stack_queue(const double_stack_queue &el) {
            left_stack = el.left_stack;
            right_stack = el.right_stack;
            left_max = el.left_max;
            left_min = el.left_min;
        }

        double_stack_queue(double_stack_queue &&el) noexcept {
            left_stack = std::move(el.left_stack);
            right_stack = std::move(el.right_stack);
            left_max = el.left_max;
            left_min = el.left_min;
        }

        void push(T &&el) noexcept;

        void push(const T &el);

        double_stack_queue &operator=(double_stack_queue &&el) noexcept {
            if (this != &el) {
                left_stack = std::move(el.left_stack);
                right_stack = std::move(el.right_stack);
                left_max = el.left_max;
                left_min = el.left_min;
            }
            return *this;
        };

        double_stack_queue &operator=(const double_stack_queue &el) {
            if (this != &el) {
                left_stack = el.left_stack;
                right_stack = el.right_stack;
                left_max = el.left_max;
                left_min = el.left_min;
            }
            return *this;
        };

        T pop();

        T get_max();

        T get_min();

        size_t get_size() {
            return left_stack.get_size() + right_stack.get_size();
        };
    };

}

template<typename T>
void my::double_stack_queue<T>::push(const T &el) {
    if (left_stack.get_size() == 0) {
        left_max = el;
        left_min = el;
    } else {
        if (el > left_max) { left_max = el; }
        else if (el < left_min) { left_min = el; }
    }
    left_stack.push(el);
}


template<typename T>
void my::double_stack_queue<T>::push(T &&el) noexcept {
    if (left_stack.get_size() == 0) {
        left_max = el;
        left_min = el;
    } else {
        if (el > left_max) { left_max = el; }
        else if (el < left_min) { left_min = el; }
    }
    left_stack.push(el);
}

template<typename T>
T my::double_stack_queue<T>::pop() {
    if (right_stack.get_size() == 0) {
        while (left_stack.get_size() != 0) {
            T el = left_stack.pop();
            if (right_stack.get_size() == 0) {
                right_stack.push(elem(el, el, el));
            } else {
                elem tmp = right_stack.get_first();
                if (el < tmp.min) { right_stack.push(elem(el, el, tmp.max)); }
                else if (el > tmp.max) {
                    right_stack.push(elem(el, tmp.min, el));}
                else { right_stack.push(elem(el, tmp.max, tmp.min)); }
            }
        }
    }

    auto x = right_stack.pop();
    return x.element;
}

template<typename T>
T my::double_stack_queue<T>::get_max() {
    if (get_size() == 0) { throw empty_list_error(); }
    if (right_stack.get_size() == 0) {
        return left_max;
    }
    if (left_max > right_stack.get_first().max && left_stack.get_size() != 0) {
        return left_max;
    }
    return right_stack.get_first().max;

}

template<typename T>
T my::double_stack_queue<T>::get_min() {
    if (get_size() == 0) { throw empty_list_error(); }
    if (right_stack.get_size() == 0) {
        return left_min;
    }
    if (left_min > right_stack.get_first().min && left_stack.get_size() != 0) {
        return left_min;
    }
    return right_stack.get_first().min;
}


#endif
