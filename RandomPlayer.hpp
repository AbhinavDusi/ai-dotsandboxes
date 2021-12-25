#ifndef RANDOM_PLAYER_H
#define RANDOM_PLAYER_H

#include "Game.hpp"
#include "Player.hpp"

using namespace std;

class RandomPlayer: public Player {
    public:
    RandomPlayer(int id): Player(id) {};
    int get_move(Game& game); 
}; 

int RandomPlayer::get_move(Game &game) {
    return rng()%game._moves.size();
}

#endif