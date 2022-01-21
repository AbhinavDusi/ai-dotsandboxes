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
    NeuralNet *target_net;
    Game get_random_game_state(int width, int height) const;
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

Game DQLPlayer::get_random_game_state(int width, int height) const {
    Game game(width, height);
    int num_moves = rng()%(2*width*height+width+height-1);
    for (int i = 0; i < num_moves; i++) {
        game.move(_id, rng()%game._moves.size());
    }
    return game;
}

void DQLPlayer::exp_decay(double *x, double x_0, double decay, int n) {
    *x = x_0*exp(-1*decay*n);
}    

DQLPlayer::DQLPlayer(int id, int width, int height): Player(id) {
    int training_examples = 10; 

    double alpha_0 = 0.5;
    double alpha_decay = 0.001;

    double eta_0 = 0.15;
    double eta_decay = 0.001; 

    double gamma = 0.0; 

    int update_target = 10;

    int layer_size = 4*width*height;
    vector<int> topology; 
    topology.push_back(layer_size);
    topology.push_back(layer_size);
    topology.push_back(layer_size);

    policy_net = new NeuralNet(topology, alpha_0, eta_0);
    target_net = new NeuralNet(topology, alpha_0, eta_0); 
    
    for (int i = 0; i < training_examples; i++) {
        if (i%update_target == 0) target_net->load(*policy_net);
        
        exp_decay(&(policy_net->_alpha), alpha_0, alpha_decay, i);
        exp_decay(&(policy_net->_eta), eta_0, eta_decay, i);

        Game random_game = get_random_game_state(width, height);
        vector<double> state = flatten_game_image(random_game);
        policy_net->feed_forward(state); 

        vector<double> target(layer_size, 0);
        for (int j = 0; j < random_game._moves.size(); j++) {
            Game random_game_clone = random_game.get_clone();
            int prev_score = random_game_clone.get_score(_id);
            random_game_clone.move(_id, j);
            int next_score = random_game_clone.get_score(_id);
            vector<double> new_state = flatten_game_image(random_game_clone);
            double reward = next_score-prev_score;

            int action = random_game._moves[j].idx;

            target_net->feed_forward(new_state);
            vector<double> target_qvals = target_net->get_result();
            double max_quality = -1;
            for (int k = 0; k < random_game_clone._moves.size(); k++) {
                max_quality = max(max_quality, target_qvals[random_game_clone._moves[k].idx]);
            }

            target[action] = reward+gamma*max_quality;
        }
        policy_net->back_prop(target); 
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
