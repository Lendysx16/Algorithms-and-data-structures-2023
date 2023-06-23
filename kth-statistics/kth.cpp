#include <iostream>
#include <fstream>
#include <ctime>
#include "stack.h"


template<typename T>
size_t partition(T *arr, size_t lo_index, size_t hi_index);

template<typename T>
void find_k_statistics(T *arr, size_t k1,size_t k2, size_t lo_index, size_t hi_index);


int main(int argc, char **argv) {
    auto timenow = time(nullptr);
    std::ifstream input = std::ifstream(argv[1]);
    if(argc < 3){
        return 3;
    }
    if(!input){
        input.close();
        std::cerr << "No input file";
        return 1;
    }
    std::ofstream output = std::ofstream(argv[2]);
    if(!output){
        input.close();
        output.close();
        std::cerr << "No output file";
        return 2;
    }
    size_t n;
    size_t k1;
    size_t k2;
    int A;
    int B;
    int C;
    int x1;
    int x2;
    input >> n >> k1 >> k2;
    input >> A >> B >> C >> x1 >> x2;
    input.close();
    auto arr = new int[n];
    arr[0] = x1;
    arr[1] = x2;
    for (size_t i = 2; i < n; ++i) {
        arr[i] = (A * arr[i - 2] + B * arr[i - 1] + C);
    }
    find_k_statistics(arr, k1, k2, 0, n - 1);
    for(auto i = k1 - 1; i < k2; ++i){
        output << arr[i];
        if( i != k2 - 1){
            output << ' ';
        }
    }
    output.close();
    delete[] arr;
    std::cout << time(nullptr) - timenow;
}


template<typename T>
void find_k_statistics(T *arr, size_t k1, size_t k2, size_t lo_index, size_t hi_index) {
    auto stackLeft = my::stack<size_t>();
    auto stackRight = my::stack<size_t>();
    if (lo_index >= hi_index) {
        return;
    }

    size_t j = partition(arr, lo_index, hi_index);

    if (j >= k1 - 1){
        //find_k_statistics(arr, k1, k2, lo_index, j);
        stackLeft.push(lo_index);
        stackRight.push(j);
    }
    if(j < k2 - 1){
        //find_k_statistics(arr, k1, k2, j + 1, hi_index);
        stackRight.push(hi_index);
        stackLeft.push(j + 1);
    }
    size_t l, r;
    while (stackLeft.get_size() != 0 && stackRight.get_size() != 0){
        l = stackLeft.pop();
        r = stackRight.pop();
        if(l >= r) {
            continue;
        }
        j = partition(arr, l, r);
        if (j >= k1 - 1){
            stackLeft.push(l);
            stackRight.push(j);
        }
        if(j < k2 - 1){
            //find_k_statistics(arr, k1, k2, j + 1, hi_index);
            stackRight.push(r);
            stackLeft.push(j + 1);
        }
    }
}


template<typename T>
size_t partition(T *arr, size_t lo_index, size_t hi_index) {
    T support_element = arr[lo_index + (hi_index - lo_index) / 2];
    size_t i = lo_index;
    size_t j = hi_index;
    while (true) {
        while (i < hi_index && arr[i] < support_element) {
            ++i;
            if(arr[j] > support_element) --j;
        }
        while (arr[j] > support_element) {
            --j;
        }
        if (i >= j) {
            break;
        }
        std::swap(arr[i], arr[j]);
        ++i;
        --j;

    }
    return j;
}
