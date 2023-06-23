#include <iostream>

unsigned long long partition(int n, int k);



int main() {
    int n = 0;
    int k = 0;
    std::cin >> n >> k;
    std::cout << partition(n, k);
    return 0;
}


unsigned long long partition(int n, int k) {
    if(n == k) {return 1;}
    unsigned long long **arr = new unsigned long long *[2];
    for (auto i = 0; i < 2; ++i) {
        arr[i] = new unsigned long long[n];
    }
    unsigned long long x = 0;

    for (auto i = 0; i < 2; ++i) {
        for (auto j = 0; j < n; ++j) {
            if (i == 0)
                { arr[i][j] = 1; }
            else
                { arr[i][j] = 0; }

        }
        arr[i][i] = 1;
    }

    for (auto i = 1; i < k; ++i) {
        for (auto j = i; j < n; ++j) {
            arr[1][j] = arr[0][j - 1];
            if (j > i + 1) {
                arr[1][j] += arr[1][j - i - 1];
            }
        }
        if(i == k - 1){
            x = arr[1][n - 1];
        }
        for(auto swap_it = 0; swap_it < n; ++swap_it){
            arr[0][swap_it] = arr[1][swap_it];
            arr[1][swap_it] = 0;
        }
    }


    for (auto i = 0; i < 2; ++i) {
        delete[] arr[i];
    }
    delete[] arr;

    return x;
}
