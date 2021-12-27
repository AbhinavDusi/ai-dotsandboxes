#ifndef DRL_PLAYER_H
#define DRL_PLAYER_H

#include "Game.hpp"
#include "Player.hpp"

using namespace std;

class DRLPlayer: public Player {
    public:
    DRLPlayer(int id): Player(id) {};
    int get_move(Game& game); 
}; 

int DRLPlayer::get_move(Game &game) {
    return 0;
}

#endif