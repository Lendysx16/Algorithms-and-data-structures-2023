#include "game_cards.h"


void game::load_game_file(std::ifstream &file) {
    unsigned char a;
    unsigned char b;
    unsigned short val;
    for (size_t i = 0; i < 52; ++i) {
        file >> a;
        if (a == '1') {
            val = 10;
            file >> a;
        } else {
            if (a <= '9') { val = a - '0'; }
            else {
                switch (a) {
                    case 'A':
                        val = 14;
                        break;
                    case 'K':
                        val = 13;
                        break;
                    case 'Q':
                        val = 12;
                        break;
                    case 'J':
                        val = 11;
                        break;
                    default:
                        throw unknown_symbol();
                }
            }
        }
        file >> b;
        if (i < 26) {
            player_one.push({val, b});
        } else {
            player_two.push({val, b});
        }

    }
}

winner game::make_a_move() {
    size_t fst_size = player_one.get_size();
    size_t snd_size = player_two.get_size();
    if (fst_size == 0 && snd_size == 0) {
        winner_is_decided = true;
        return winner::draw;
    }
    if (fst_size == 0) {
        winner_is_decided = true;
        return winner::second;
    }
    if (snd_size == 0) {
        winner_is_decided = true;
        return winner::first;
    }
    cards player_one_card = player_one.pop();
    cards player_two_card = player_two.pop();
    if (player_one_card.card_value > player_two_card.card_value) {
        if (player_one_card.card_value == 14 && player_two_card.card_value == 2) {
            player_two.push(player_one_card);
            player_two.push(player_two_card);
            return winner::second;
        }

        player_one.push(player_one_card);
        player_one.push(player_two_card);
        return winner::first;

    }
    if (player_one_card.card_value < player_two_card.card_value) {
        if (player_one_card.card_value == 2 && player_two_card.card_value == 14) {
            player_one.push(player_one_card);
            player_one.push(player_two_card);
            return winner::first;
        }
        player_two.push(player_one_card);
        player_two.push(player_two_card);
        return winner::second;

    }

    my::queue<cards> cards_to_push = my::queue<cards>();
    winner conflict = conflict_situation(cards_to_push);
    if (conflict == winner::draw) { return winner::draw; }

    if (conflict == winner::first) {
        player_one.push(player_one_card);
        player_one.push(player_two_card);
        while (cards_to_push.get_size() != 0) {
            player_one.push(cards_to_push.pop());
        }

    }
    else {
        player_two.push(player_one_card);
        player_two.push(player_two_card);
        while (cards_to_push.get_size() != 0) {
            player_two.push(cards_to_push.pop());
        }
    }
    return conflict;

}


winner game::conflict_situation(my::queue<cards> &x) {
    size_t fst_size = player_one.get_size();
    size_t snd_size = player_two.get_size();
    if (fst_size == 0 && snd_size == 0) {
        winner_is_decided = true;
        return winner::draw;
    }
    if (fst_size == 0) {
        winner_is_decided = true;
        return winner::second;
    }
    if (snd_size == 0) {
        winner_is_decided = true;
        return winner::first;
    }
    cards player_one_card = player_one.pop();
    cards player_two_card = player_two.pop();
    if (player_one_card.card_value > player_two_card.card_value) {
        if (player_one_card.card_value == 14 && player_two_card.card_value == 2) {
            x.push(player_one_card);
            x.push(player_two_card);
            return winner::second;
        }
        x.push(player_one_card);
        x.push(player_two_card);
        return winner::first;
    }
    if (player_one_card.card_value < player_two_card.card_value) {
        if (player_one_card.card_value == 2 && player_two_card.card_value == 14) {
            x.push(player_one_card);
            x.push(player_two_card);
            return winner::first;
        }
        x.push(player_one_card);
        x.push(player_two_card);
        return winner::second;
    }

    x.push(player_one_card);
    x.push(player_two_card);
    return conflict_situation(x);


}