

#ifndef MST_SIMPLE_DSU_H
#define MST_SIMPLE_DSU_H

#include <iostream>

namespace my {
    class DSU {
    private:
        int *arr = nullptr;
        size_t size;
    public:
        explicit DSU(size_t size_) {
            this->size = size_;
            arr = new int[size];
            for (auto i = 0; i < size; ++i) {
                arr[i] = i;
            }

        }

        ~DSU() {
            delete[] arr;
        }

        int get(int key) {
            if (arr[key] == key) {
                return key;
            }
            return get(arr[key]);
        }
        void union_dsu(int a, int b){
            int a_gr = get(a);
            int b_gr = get(b);
            if(a_gr == b_gr) { return;}
            if(a_gr != a && b_gr != b){
                for(auto i = 0; i < size; ++i){
                    if(arr[i] == a_gr){
                        arr[i] = b_gr;
                    }
                }
            }
            else{
                if(a_gr != a){
                    arr[b] = a_gr;
                }
                else{
                    arr[a] = b_gr;
                }
            }
        }
    };
}
#endif //MST_SIMPLE_DSU_H
