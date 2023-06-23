#include <iostream>
#include "pr_queue.h"
#include <fstream>
#include <cstring>

int func_case_help_strcmp(char *str) {
    if (strcmp(str, "push") == 0) {
        return 0;
    }
    if (strcmp(str, "extract-min") == 0) {
        return 1;
    }
    return 2;
}


int main(int argc, char **argv) {
    if (argc < 3) {
        std::cerr << "Specify input and output file names";
        return 1;
    }
    std::ifstream input = std::ifstream(argv[1]);
    if (!input) {
        std::cerr << "Input file can not be found";
        return 2;
    }
    std::ofstream output = std::ofstream(argv[2], std::ios_base::binary);

    if (!output) {
        std::cerr << "Output file can not be opened or created";
        input.close();
        return 3;
    }
    my::Node **arr = new my::Node*[100000];
    char *str = new char[256];
    int num;
    size_t counter = 0;
    int min;
    int decrease_num;
    int res_help_strcmp;
    my::pr_queue x;
    while (true){
        counter += 1;
        input >> str;
        if(input.peek() == EOF){
            break;
        }
        res_help_strcmp = func_case_help_strcmp(str);
        switch (res_help_strcmp) {
            case 0: {
                input >> num;
                arr[counter] = x.insert(num);
                break;
            }
            case 1: {
                try {
                    min = x.extract_min();
                    output << min;
                }
                catch (std::out_of_range &e){
                    output<< "*";
                }
                output << '\n';
                break;
            }
            case 2: {
                input >> num;
                input >> decrease_num;
                x.decrease_key(arr[num], decrease_num);
                break;
            }
            default:
                break;
        }
    }


    input.close();
    output.close();
    delete[] arr;
    delete[] str;
    return 0;
}
