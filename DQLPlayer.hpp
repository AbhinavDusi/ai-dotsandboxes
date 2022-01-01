#ifndef DQL_PLAYER_H
#define DQL_PLAYER_H

#include <vector>

#include "Game.hpp"
#include "Player.hpp"
#include "NeuralNet.hpp"

using namespace std;

typedef struct Experience {
    int state;
    int action;     
    double reward;
    int next_state;
    Experience(int state, int action, double reward, int next_state): 
        state(state), action(action), reward(reward), next_state(next_state) {};
} Experience;   

class DQLPlayer: public Player {
    public:
    DQLPlayer(int id, Game &game);
    int get_move(Game &game); 

    private:
    NeuralNet *policy_net; 
    NeuralNet *target_net;
    Experience get_random_experience() const;
}; 

Experience DQLPlayer::get_random_experience() const {
    return Experience(0, 0, 0, 0); 
}

DQLPlayer::DQLPlayer(int id, Game &game): Player(id) {
    int training_examples = 10; 
    double alpha = 0.5;
    double eta = 0.15;
    double gamma = 0.999; 
    double epsilon = 1.0;
    double epislon_decay = 0.99/(double) training_examples;
    int update_target = 10;
    int total_moves = 2*game._width*game._height-game._width-game._height; 

    vector<int> topology; 
    topology.push_back(total_moves);
    topology.push_back(total_moves);
    topology.push_back(total_moves);

    policy_net = new NeuralNet(topology, alpha, eta);
    target_net = new NeuralNet(topology, alpha, eta); 
    
    for (int i = 0; i < training_examples; i++) {
        Experience experience = get_random_experience();

        vector<double> input;

        //policy_net.feed_forward(input); 

        vector<double> target;

        //policy_net.back_prop(target); 

        if (i%update_target == 0) {
            target_net->load(*policy_net);
        }
    }
}

int DQLPlayer::get_move(Game &game) {
    return 0;
}

#endif
