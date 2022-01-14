#ifndef PLAYER_H
#define PLAYER_H

#include <ctime>
#include <random>
#include <string>

#include "Game.hpp"

using namespace std; 

class Player {
    public:
    Player(int id) : _id(id), _score(0), _time_elapsed(0.0), _moves_taken(0) {};
    int move(Game &game); 
    virtual int get_move(Game &game) = 0; 
    virtual string get_name() = 0;
    int _id; 
    int _score;
    double _time_elapsed;
    int _moves_taken;
    static mt19937 rng;
};

mt19937 Player::rng(time(nullptr));

int Player::move(Game &game) {
    int move_idx = !game._started ? rng()%game._moves.size() : get_move(game);
    int scored = game.move(_id, move_idx); 
    _score += scored;
    _moves_taken++;
    return scored;
}

#endif
