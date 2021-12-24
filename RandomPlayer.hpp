#ifndef RANDOM_PLAYER_H
#define RANDOM_PLAYER_H

#include <random>

#include "Game.hpp"
#include "Player.hpp"

using namespace std;

class RandomPlayer: public Player {
    public:
    RandomPlayer();
    int move(const vector<Move>& moves);

    int score;

    private:
    static mt19937 rng; 
}; 

mt19937 RandomPlayer::rng(time(nullptr));

RandomPlayer::RandomPlayer() {
    score = 0; 
}

int RandomPlayer::move(const vector<Move>& moves) {
    return rng()%moves.size();
}

#endif