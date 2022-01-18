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
    int choose_action(Game &game) const;
    Experience get_random_experience(double epsilon, int width, int height) const;
    vector<double> flatten_game_image(Game &game) const;
    static void exp_decay(double *x, double x_0, double decay, int n); 
}; 

int DQLPlayer::choose_action(Game &game) const {
    vector<double> input = flatten_game_image(game); 
    policy_net->feed_forward(input); 

    vector<double> result = policy_net->get_result();

    int move_idx = 0;
    double max_quality = -1;
    for (int i = 0; i < game._moves.size(); i++) {
        if (result[game._moves[i].idx] > max_quality) {
            max_quality = result[game._moves[i].idx];
            move_idx = i;
        }
    }
    return move_idx;
}

vector<double> DQLPlayer::flatten_game_image(Game &game) const {
    vector<double> flattened_image;
    for (int i = 0; i < game._height; i++) {
        for (int j = 0; j < game._width; j++) {
            for (int k = 0; k < 4; k++) {
                flattened_image.push_back(game._game_image[i][j][k]);
            }
        }
    }
    return flattened_image;
}

Experience DQLPlayer::get_random_experience(double epsilon, int width, int height) const {
    Game game(width, height);
    int num_moves = rng()%(2*width*height+width+height-1);
    for (int i = 0; i < num_moves; i++) {
        game.move(_id, rng()%game._moves.size());
    }
    vector<double> state = flatten_game_image(game);

    int action = 0; 
    bool explore = rng()/(double) rng.max()<epsilon;
    if (explore) {
        action = rng()%game._moves.size();
    } else {
        action = choose_action(game);
    }
    game.move(_id, action);

    vector<double> new_state = flatten_game_image(game);

    double reward = 0.0; 

    return Experience(state, action, reward, new_state); 
}

void DQLPlayer::exp_decay(double *x, double x_0, double decay, int n) {
    *x = x_0*exp(-1*decay*n);
}    

DQLPlayer::DQLPlayer(int id, int width, int height): Player(id) {
    int training_examples = 1; 

    double alpha_0 = 0.5;
    double alpha_decay = 0.001;

    double eta_0 = 0.15;
    double eta_decay = 0.001; 

    double epsilon_0 = 1.0;
    double epsilon = epsilon_0;
    double epsilon_decay = 0.001; 

    double gamma = 0.999; 

    int update_target = 10;

    int layer_size = 4*width*height;
    vector<int> topology; 
    topology.push_back(layer_size);
    topology.push_back(layer_size);
    topology.push_back(layer_size);

    policy_net = new NeuralNet(topology, alpha_0, eta_0);
    target_net = new NeuralNet(topology, alpha_0, eta_0); 
    
    for (int i = 0; i < training_examples; i++) {
        if (i%update_target == 0) {
            target_net->load(*policy_net);
        }
        
        exp_decay(&epsilon, epsilon_0, epsilon_decay, i);
        exp_decay(&(policy_net->_alpha), alpha_0, alpha_decay, i);
        exp_decay(&(policy_net->_eta), eta_0, eta_decay, i);

        Experience experience = get_random_experience(epsilon, width, height);

        vector<double> input = experience.state;
        //policy_net->feed_forward(input); 

        vector<double> target;

        //policy_net->back_prop(target); 
    }
}

int DQLPlayer::get_move(Game &game) {
    return choose_action(game);
}

#endif
