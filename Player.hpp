#ifndef PLAYER_H
#define PLAYER_H

#include "Game.hpp"

class Player {
    public:
    Player(int id) : _id(id), _score(0) {};
    virtual int move(Game &game) = 0; 

    int _id; 
    int _score;
};

#endif