#include <iostream>
#include <fstream>
#include "sort.h"
#include "my_pair.h"

typedef my::pair<int, int> intpair;

bool comp_1(intpair x1, intpair x2){
    return x1.fst_el() < x2.fst_el();
}

bool comp_2(intpair x1, intpair x2){
    return x1.snd_el() < x2.snd_el();

}

int main(int argc, char**argv){
    if(argc < 2) {
        std::cout << "No input file name";
        return 1;
    }
    auto input = std::ifstream(argv[1]);
    if(!input){
        input.close();
        std::cout << "File with that name does not exist";
        return 2;
    }
    int n;
    input >> n;
    intpair* x = new intpair[n];
    int a;
    int b;
    for(int i = 0; i < n; ++i){
        input >> a >> b;
        x[i] = intpair(a, b);
    }
    my::mergesort(x, n, comp_1);
    size_t res = my::mergesort(x, n, comp_2);
    std::cout << res;
    delete[] x;
}
