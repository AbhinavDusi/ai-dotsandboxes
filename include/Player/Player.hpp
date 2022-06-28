#ifndef PLAYER_H
#define PLAYER_H

#include <ctime>
#include <random>
#include <string>
#include <chrono>

#include "../Game/Game.hpp"

using namespace std; 
using namespace std::chrono;

class Player {
    public:
    Player(int id) : _id(id), _time_elapsed(0.0), _moves_taken(0) {};
    int move(Game &game); 
    virtual int get_move(Game &game) = 0; 
    virtual string get_name() = 0;
    double get_avg_move_time() const { return _time_elapsed/_moves_taken; }
    int _id; 
    double _time_elapsed;
    int _moves_taken;
    static mt19937 rng;
};

mt19937 Player::rng(time(nullptr));

int Player::move(Game &game) {
    auto start = high_resolution_clock::now();
    int move_idx = !game._started ? rng()%game._moves.size() : get_move(game);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end-start);
    int scored = game.move(_id, move_idx); 
    _moves_taken++;
    _time_elapsed += duration.count();
    return scored;
}

#endif
