#include <iostream>
#include <fstream>
#include "sort.h"
#include "my_pair.h"

typedef my::pair<int, float> student_pair;

int main(int argc, char** argv) {
    if(argc < 2){
        std::cerr << "No input file";
        return 1;
    }
    std::ifstream input_file = std::ifstream(argv[1]);
    if(!input_file.is_open()){
        input_file.close();
        std::cerr << "No file with name " << argv[1];
        return 2;
    }
    int n;
    float res;
    student_pair *arr;
    input_file >> n;
    arr = new student_pair [n];
    for(int i = 0; i < n; ++i){
        input_file >> res;
        arr[i] = student_pair(i + 1, res);
    }
    my::mergesort(arr, n);
    std::cout << arr[0].fst_el() << ' ' << arr[n / 2].fst_el() <<' ' << arr[n - 1].fst_el();
    delete[] arr;
    input_file.close();
    return 0;
}
