#ifndef ALGORITHMIC_PLAYER_H
#define ALGORITHMIC_PLAYER_H

#include "Game.hpp"
#include "Player.hpp"

using namespace std;

class AlgorithmicPlayer: public Player {
    public:
    AlgorithmicPlayer(int id): Player(id) {};
    int get_move(Game& game); 
    string get_name() { return "Algorithmic"; }
}; 

int AlgorithmicPlayer::get_move(Game &game) {
    return 0;
}

#endif