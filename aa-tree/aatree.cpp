#include <iostream>
#include "AAtree.h"
#include <fstream>

int main(int argc, char** argv) {
    if(argc < 3){
        std::cerr << "Specify names of input and output files";
        return 1;
    }
    std::ifstream input = std::ifstream(argv[1]);
    if(!input){
        input.close();
        std::cerr << "No input file";
        return 2;
    }
    std::ofstream output = std::ofstream(argv[2]);
    if(!output){
        input.close();
        output.close();
        std::cerr << "No output file";
        return 3;
    }
    my::AAtree<int> tree;
    size_t n;
    int num;
    char sym;
    input >> n;
    for(size_t i = 0; i < n; ++i){
        input >> sym;
        input >> num;
        switch (sym) {
            case '?':
                output << (tree.find(num) ? "true" : "false");
                break;
            case '+':
                tree.insert(num);
                output << tree.balance();
                break;
            case '-':
                tree.remove(num);
                output << tree.balance();
                break;
            default:
                break;


        }

            output << '\n';
        
    }

    input.close();
    output.close();
    return 0;
}
