#ifndef RANDOM_PLAYER_H
#define RANDOM_PLAYER_H

#include <random>
#include <ctime>

#include "Game.hpp"
#include "Player.hpp"

using namespace std;

class RandomPlayer: public Player {
    public:
    RandomPlayer(int id): Player(id) {};
    int move(Game &game);

    private:
    static mt19937 rng;
}; 

mt19937 RandomPlayer::rng(time(nullptr));

int RandomPlayer::move(Game &game) {
    int scored = game.move(_id, rng()%game._moves.size()); 
    _score += scored;
    return scored;
}

#endif