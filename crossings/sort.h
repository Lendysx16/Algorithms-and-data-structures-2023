
#ifndef TASK3_SORT_H
#define TASK3_SORT_H
#include <iostream>


template <typename T>
using comparator = bool(*)(T x, T y);


namespace my{
template<typename T>
size_t mergesort(T *array, int Len, comparator<T> k) {
    T *tmp = new T[Len];
    size_t cnt = 0;
    bool res;
    T *from = array;
    T *to = tmp;
    for (int step = 1; step < Len; step *= 2) {
        int start1;
        int end1;
        int start2;
        int end2;
        int index = 0;
        for (int start = 0; start < Len; start += 2 * step) {
            start1 = start;
            end1 = start1 + step;
            end1 = (end1 < Len) ? end1 : Len;
            start2 = end1;
            end2 = start2 + step;
            end2 = (end2 < Len) ? end2 : Len;
            while (start1 < end1 && start2 < end2) {
                res = k(from[start1], from[start2]);
                to[index++] = res ? from[start1++] : from[start2++];
                if(!res) {cnt += end1 - start1;}
            }


            while (start1 < end1) {
                to[index++] = from[start1++]; }
            while (start2 < end2) {
                to[index++] = from[start2++]; }
        }
        std::swap(from, to);
    }
    if (from != array) {
        int i = 0;
        while (i < Len) {
            array[i] = tmp[i];
            ++i;
        }
    }
    delete[] tmp;
    return cnt;
}
}
#endif //TASK3_SORT_H
