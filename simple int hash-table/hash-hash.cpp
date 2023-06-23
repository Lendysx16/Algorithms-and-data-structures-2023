#include <iostream>
#include <fstream>
#include "hash_set.h"
int main(int argc, char **argv) {
    if(argc < 3){
        std::cerr << "Specify input and output files";
        return 1;
    }
    std::ifstream input = std::ifstream(argv[1]);
    if(!input){
        input.close();
        return 2;
    }
    std::ofstream output = std::ofstream(argv[2]);
    if(!output){
        output.close();
        input.close();
        return 3;
    }
    auto x = my::hash_set_int();
    int n;
    bool res;
    int num;
    input >> n;
    char c;
    for(int i = 0; i < n; ++i){
        input >> c;
        input >> num;
        switch (c) {
            case '+':
                x.add(num);
                break;
            case '-':
                x.remove(num);
                break;
            case '?':
                res = x.find_el(num);
                if(res){
                    output << "true\n";
                }
                else{
                    output << "false\n";
                }
                break;
            default:
                std::cerr << "Unknown command";
                return 4;
        }
    }
    input.close();
    output.close();
    return 0;
}
