#ifndef DQL_PLAYER_H
#define DQL_PLAYER_H

#include <vector>

#include "Game.hpp"
#include "Player.hpp"
#include "NeuralNet.hpp"

using namespace std;

typedef struct Experience {
    vector<double> state;
    int action;     
    double reward;
    vector<double> next_state;
    Experience(vector<double> state, int action, double reward, vector<double> next_state): 
        state(state), action(action), reward(reward), next_state(next_state) {};
} Experience;   

class DQLPlayer: public Player {
    public:
    DQLPlayer(int id, int width, int height);
    int get_move(Game &game); 
    string get_name() { return "Deep Q Learning"; }

    private:
    NeuralNet *policy_net; 
    NeuralNet *target_net;
    Experience get_random_experience(double epsilon) const;
    static void exp_decay(double *x, double x_0, double decay, int n); 
}; 

Experience DQLPlayer::get_random_experience(double epsilon) const {
    // Get random state


    // Choose action based on explore vs exploit
    int action = 0; 
    bool explore = rng()/(double) rng.max()<epsilon;
    if (explore) {
        
    } else {

    }

    // Get new state 


    // Get reward of the action
    double reward = 0.0; 

    return Experience(vector<double>(), action, reward, vector<double>()); 
}

void DQLPlayer::exp_decay(double *x, double x_0, double decay, int n) {
    *x = x_0*exp(-1*decay*n);
}    

DQLPlayer::DQLPlayer(int id, int width, int height): Player(id) {
    int training_examples = 2000; 

    double alpha_0 = 0.5;
    double alpha_decay = 0.001;

    double eta_0 = 0.15;
    double eta_decay = 0.001; 

    double epsilon_0 = 1.0;
    double epsilon = epsilon_0;
    double epsilon_decay = 0.001; 

    double gamma = 0.999; 

    int update_target = 10;

    int input_size = 4*width*height;
    int output_size = 2*width*height+width+height; 

    vector<int> topology; 
    topology.push_back(input_size);
    topology.push_back((input_size+output_size)/2);
    topology.push_back(output_size);

    policy_net = new NeuralNet(topology, alpha_0, eta_0);
    target_net = new NeuralNet(topology, alpha_0, eta_0); 
    
    for (int i = 0; i < training_examples; i++) {
        if (i%update_target == 0) {
            target_net->load(*policy_net);
        }
        
        exp_decay(&epsilon, epsilon_0, epsilon_decay, i);
        exp_decay(&(policy_net->_alpha), alpha_0, alpha_decay, i);
        exp_decay(&(policy_net->_eta), eta_0, eta_decay, i);

        Experience experience = get_random_experience(epsilon);

        vector<double> input = experience.state;
        //policy_net->feed_forward(input); 

        vector<double> target;

        //policy_net->back_prop(target); 
    }
}

int DQLPlayer::get_move(Game &game) {
    vector<double> input; 

    //policy_net->feed_forward(input); 

    vector<double> result = policy_net->get_result();

    return 0;
}

#endif
