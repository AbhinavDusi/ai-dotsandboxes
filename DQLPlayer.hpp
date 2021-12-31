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
    NeuralNet *policy_net;
    NeuralNet *target_net;
}; 

DQLPlayer::DQLPlayer(int id, Game &game): Player(id) {
    double alpha = 0.5;
    double eta = 0.15;
    double gamma = 0.999; 
    double epsilon = 0.05;
    int update_target = 10;
    int num_episodes = 1;
    int total_moves = 2*game._width*game._height-game._width-game._height; 

    vector<int> topology; 
    topology.push_back(total_moves);
    topology.push_back(total_moves);
    topology.push_back(total_moves);

    policy_net = new NeuralNet(topology, alpha, eta);
    target_net = new NeuralNet(topology, alpha, eta); 
    target_net->load(*policy_net); 
    
    for (int i = 0; i < num_episodes; i++) {

    }
}

int DQLPlayer::get_move(Game &game) {
    return 0;
}

#endif
