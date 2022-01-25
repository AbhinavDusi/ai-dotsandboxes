#ifndef HUMAN_PLAYER_H
#define HUMAN_PLAYER_H

#include "Game.hpp"
#include "Player.hpp"

using namespace std;

class HumanPlayer: public Player {
    public:
    HumanPlayer(int id): Player(id) {};
    int get_move(Game &game); 
    string get_name() { return "Human"; }
}; 

int HumanPlayer::get_move(Game &game) {
    return 0;
}

#endif