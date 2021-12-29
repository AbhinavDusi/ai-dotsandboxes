#ifndef DQL_PLAYER_H
#define DQL_PLAYER_H

#include <vector>

#include "Game.hpp"
#include "Player.hpp"
#include "NeuralNet.hpp"

using namespace std;

class DQLPlayer: public Player {
    public:
    DQLPlayer(int id, Game &game);
    int get_move(Game &game); 

    private:
    NeuralNet *net;
}; 

DQLPlayer::DQLPlayer(int id, Game &game): Player(id) {
    vector<int> topology; 
    int total_moves = 2*game._width*game._height-game._width-game._height; 
    topology.push_back(total_moves);
    topology.push_back(total_moves);
    topology.push_back(total_moves);

    net = new NeuralNet(topology);


}

int DQLPlayer::get_move(Game &game) {
    return 0;
}

#endif