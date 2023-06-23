#include <iostream>
#include "game_cards.h"

int main(int argc, char** argv) {
    if(argc < 2){
        std::cout << "not enough arguments";
        return 1;
    }
    char *input = argv[1];
    auto file = std::ifstream(input);
    if(!file){
        std::cout << input << " can not be opened";
        return 2;
    }
    auto c = game();
    c.load_game_file(file);
    file.close();
    winner result;
    unsigned long counter = 0;
    while (!c.end_of_the_game()) {
        result = c.make_a_move();
        ++counter;
        if (counter > 1000000) {
            std::cout << "unknown";
            return 0;
        }
    }
    switch (result) {
        case first:
            std::cout << "first";
            break;
        case second:
            std::cout << "second";
            break;
        case draw:
            std::cout << "draw";
            break;
    }
    return 0;
}
