#ifndef HUMAN_PLAYER_H
#define HUMAN_PLAYER_H

#include "../../Game/Game.hpp"
#include "../Player.hpp"

#include <iostream>

using namespace std;

class HumanPlayer: public Player {
    public:
    HumanPlayer(int id);
    int get_move(Game &game); 
    string get_name() { return "Human"; }
}; 

HumanPlayer::HumanPlayer(int id): Player(id) {
    cout << "Human Player: Choose move by typing row, col, and direction:\n" << endl;
    cout << "0=up; 1=right; 2=down; 3=left\n" << endl;
}

int HumanPlayer::get_move(Game &game) {
    cout << "Current game: " << endl;
    game.print();

    bool invalid_move = true; 
    while (invalid_move) {
        int row, col, direction;
        cin >> row >> col >> direction; 

        for (int i = 0; i < game._moves.size(); i++) {
            if (game._moves[i].row==row 
                && game._moves[i].col==col 
                && game._moves[i].direction==direction) {
                return i;
            }
        }

        cout << "Invalid move. Choose again." << endl;
    }

    return 0;
}

#endif