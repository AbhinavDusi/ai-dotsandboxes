#ifndef PLAYER_H
#define PLAYER_H

#include <ctime>
#include <random>

#include "Game.hpp"

class Player {
    public:
    Player(int id) : _id(id), _score(0) {};
    int move(Game &game); 
    virtual int get_move(Game &game) = 0; 

    int _id; 
    int _score;
    static mt19937 rng;
};

mt19937 Player::rng(time(nullptr));

int Player::move(Game &game) {
    int scored = game.move(_id, get_move(game)); 
    _score += scored;
    return scored;
}

#endif