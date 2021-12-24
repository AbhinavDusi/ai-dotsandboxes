#ifndef AI_PLAYER_H
#define AI_PLAYER_H

#include <random>
#include <ctime>

#include "Game.hpp"
#include "Player.hpp"

using namespace std;

class AIPlayer: public Player {
    public:
    AIPlayer(int id) : Player(id) {};
    int move(Game &game);
}; 

int AIPlayer::move(Game &game) {
    return game.move(_id, 0);
}

#endif