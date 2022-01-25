#ifndef DQL_PLAYER_H
#define DQL_PLAYER_H

#include <vector>

#include "Game.hpp"
#include "Player.hpp"
#include "NeuralNet.hpp"

using namespace std;

class DQLPlayer: public Player {
    public:
    DQLPlayer(int id, int width, int height);
    int get_move(Game &game); 
    string get_name() { return "Deep Q Learning"; }

    private:
    NeuralNet *policy_net; 
    vector<double> flatten_game_image(Game &game) const;
    static void exp_decay(double *x, double x_0, double decay, int n); 
}; 

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

void DQLPlayer::exp_decay(double *x, double x_0, double decay, int n) {
    *x = x_0*exp(-1*decay*n);
}    

DQLPlayer::DQLPlayer(int id, int width, int height): Player(id) {
    int episodes = 2000; 

    double alpha_0 = 0.5;
    double alpha_decay = 0.001;

    double eta_0 = 0.15;
    double eta_decay = 0.001; 

    double epsilon_0 = 0.95;
    double epsilon = epsilon_0;
    double epsilon_decay = 0.001;

    double gamma = 0.999; 

    int layer_size = 4*width*height;
    vector<int> topology; 
    topology.push_back(layer_size);
    topology.push_back(layer_size);
    topology.push_back(layer_size);

    policy_net = new NeuralNet(topology, alpha_0, eta_0);

    for (int i = 0; i < episodes; i++) {
        Game game(width, height);
        vector<double> state_0 = flatten_game_image(game); 

        exp_decay(&epsilon, epsilon_0, epsilon_decay, i);
        exp_decay(&(policy_net->_alpha), alpha_0, alpha_decay, i);
        exp_decay(&(policy_net->_eta), eta_0, eta_decay, i);

        for (int l = 0; l < 2*width*height+width+height; l++) {
            bool explore = (double) rng()/rng.max() > epsilon; 
            if (explore) {

            } else {

            }
        }
    }
}

int DQLPlayer::get_move(Game &game) {
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

#endif
