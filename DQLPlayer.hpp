#ifndef DQL_PLAYER_H
#define DQL_PLAYER_H

#include <vector>

#include "Game.hpp"
#include "Player.hpp"
#include "NeuralNet.hpp"
#include "ReplayMemory.hpp"

using namespace std;

class DQLPlayer: public Player {
    public:
    DQLPlayer(int id, int width, int height);
    int get_move(Game &game); 
    string get_name() { return "Deep Q Learning"; }

    private:
    NeuralNet *policy_net; 
    NeuralNet *target_net;
    vector<double> flatten_game_image(Game &game) const;
    int choose_action(Game &game, NeuralNet **net);
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

int DQLPlayer::choose_action(Game &game, NeuralNet **net) {
    vector<double> input = flatten_game_image(game); 
    (*net)->feed_forward(input); 

    vector<double> result = (*net)->get_result();

    int action = 0;
    double max_quality = -1;
    for (int i = 0; i < game._moves.size(); i++) {
        if (result[game._moves[i].idx] > max_quality) {
            max_quality = result[game._moves[i].idx];
            action = i;
        }
    }
    return action;
}

void DQLPlayer::exp_decay(double *x, double x_0, double decay, int n) {
    *x = x_0*exp(-1*decay*n);
}    

DQLPlayer::DQLPlayer(int id, int width, int height): Player(id) {
    int capacity = 100;
    ReplayMemory rm(capacity);

    int episodes = 2000; 

    double alpha = 0.5;
    double eta = 0.15;

    double epsilon_0 = 0.99;
    double epsilon = epsilon_0;
    double epsilon_decay = 0.001;

    int update_target = 10;

    int layer_size = 4*width*height;
    vector<int> topology; 
    topology.push_back(layer_size);
    topology.push_back(layer_size);
    topology.push_back(layer_size);

    policy_net = new NeuralNet(topology, alpha, eta);

    for (int i = 0; i < episodes; i++) {
        Game game(width, height);
        vector<double> state_0 = flatten_game_image(game); 

        if (i%update_target==0) policy_net->load(*target_net);

        exp_decay(&epsilon, epsilon_0, epsilon_decay, i);

        while (!game._finished) {
            bool explore = (double) rng()/rng.max() > epsilon; 
            int action = 0;
            if (explore) action = rng()%game._moves.size();
            else action = choose_action(game, &target_net);

            game.move(action);
        }
    }
}

int DQLPlayer::get_move(Game &game) {
    return choose_action(game, &policy_net);
}

#endif