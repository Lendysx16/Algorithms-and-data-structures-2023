#include <iostream>
#include <fstream>
#include "queue_minmax.h"

int main(int argc, char **argv) {
    if (argc < 3) {
        return 1;
    }

    std::ifstream file_input = std::ifstream(argv[1]);
    if (!file_input.is_open()) {
        file_input.close();
        return 2;
    }
    std::ofstream file_output = std::ofstream(argv[2]);
    if (!file_output.is_open()) {
        file_input.close();
        file_output.close();
        return 3;
    }
    int n;
    int tmp;
    char command;
    file_input >> n;
    auto x = my::double_stack_queue<int>();
    for (int i = 0; i < n; ++i) {
        file_input >> command;
        switch (command) {
            case '+': {
                file_input >> tmp;
                x.push(tmp);
                break;
            }
            case '?': {
                file_output << (x.get_max() - x.get_min()) << std::endl;
                break;
            }
            case '-': {
                x.pop();
                break;
            }
            default:
                std::cerr << "Unexpected argument";
                break;
        }
    }


    return 0;
}
