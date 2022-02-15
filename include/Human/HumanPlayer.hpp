#ifndef HUMAN_PLAYER_H
#define HUMAN_PLAYER_H

#include "../Game.hpp"
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
    cout << "Human Player: Choose move by selecting row, col, and direction:" << endl;
    cout << "0=up; 1=right; 2=down; 3=left" << endl;
}

int HumanPlayer::get_move(Game &game) {
    cout << "Current game: " << endl;
    game.print();

    int row, col, direction;
    cin >> row >> col >> direction; 

    for (int i = 0; i < game._moves.size(); i++) {
        if (game._moves[i].row==row && game._moves[i].col==col && game._moves[i].direction==direction) {
            return i;
        }
    }

    return 0;
}

#endif