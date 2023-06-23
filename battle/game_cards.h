#include "queue.h"
#include <fstream>

#ifndef TASK2_CARDS_H
#define TASK2_CARDS_H


enum winner{
    first,
    second,
    draw
};

struct cards {
    unsigned short card_value;
    unsigned char card_suite;

    cards() {
        card_value = 0;
        card_suite = '0';
    }

    cards(unsigned short val, unsigned char suite) : card_value(val), card_suite(suite) {};
};


class game {
private:
    bool winner_is_decided = false;
    winner conflict_situation(my::queue<cards> &x);
    my::queue<cards> player_one;
    my::queue<cards> player_two;
public:
    game() = default;
    bool end_of_the_game() const {
        return winner_is_decided;
    }
    void load_game_file(std::ifstream &file);
    winner make_a_move();
};


class unknown_symbol : std::exception {
public:
    unknown_symbol() = default;

    ~unknown_symbol() override = default;

    const char *what() const noexcept override {
        return "Unknown symbol in file";
    }
};

#endif //TASK2_CARDS_H
