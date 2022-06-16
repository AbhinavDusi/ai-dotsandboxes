#ifndef DQL_PLAYER_H
#define DQL_PLAYER_H

#include <vector>
#include <chrono>

#include "../Game.hpp"
#include "../Player.hpp"
#include "NeuralNet.hpp"
#include "ReplayMemory.hpp"

using namespace std;
using namespace std::chrono;

class DQLPlayer: public Player {
    public:
    DQLPlayer(int id, int width, int height);
    int get_move(Game &game); 
    string get_name() { return "Deep Q Learning"; }

    private:
    NeuralNet *policy_net; 
    NeuralNet *target_net;
    vector<double> flatten_game_image(Game &game) const;
    pair<int, double> choose_action(Game &game, NeuralNet **net);
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

pair<int, double> DQLPlayer::choose_action(Game &game, NeuralNet **net) {
    (*net)->feed_forward(flatten_game_image(game)); 
    vector<double> result = (*net)->get_result();

    int action = 0;
    double max_quality = -1;
    for (int i = 0; i < game._moves.size(); i++) {
        if (result[game._moves[i].idx] > max_quality) {
            max_quality = result[game._moves[i].idx];
            action = i;
        }
    }
    return make_pair(action, max_quality);
}

void DQLPlayer::exp_decay(double *x, double x_0, double decay, int n) {
    *x = x_0*exp(-1*decay*n);
}    

DQLPlayer::DQLPlayer(int id, int width, int height): Player(id) {
    auto start = high_resolution_clock::now();

    int capacity = 20000;
    ReplayMemory rm(capacity);

    int minibatch_size = 16;

    int episodes = 1000; 

    double alpha = 0.15;

    double epsilon_0 = 0.99;
    double epsilon = epsilon_0;
    double epsilon_decay = 0.001;

    double gamma = 0.9;

    int update_target = 10;

    int layer_size = 4*width*height;
    vector<int> topology; 
    topology.push_back(layer_size);
    topology.push_back(2*layer_size);
    topology.push_back(2*layer_size);
    topology.push_back(layer_size);

    policy_net = new NeuralNet(topology, alpha);
    target_net = new NeuralNet(topology, alpha);

    for (int i = 0; i < episodes; i++) {
        if (i%update_target==0) target_net->load(*policy_net);

        exp_decay(&epsilon, epsilon_0, epsilon_decay, i);

        Game game(width, height);

        while (!game._finished) {
            Game initial = game.get_clone();

            bool explore = (double) rng()/rng.max() > epsilon; 
            int action_idx = 0;
            if (explore) action_idx = rng()%game._moves.size();
            else action_idx = choose_action(game, &policy_net).first;
            Move action = game._moves[action_idx];

            double reward = game.move(_id, action_idx);

            Game next = game.get_clone();
            
            rm.add_experience(Experience(initial, action, reward, next));

            if (rm.can_provide_sample(minibatch_size)) {
                vector<Experience> sample = rm.get_sample(minibatch_size);
                for (int j = 0; j < minibatch_size; j++) {
                    Experience experience = sample[j]; 

                    double bellman = experience.reward;

                    policy_net->feed_forward(flatten_game_image(experience.state_0));
                    vector<double> target = policy_net->get_result();
                    
                    bool terminal = experience.state_1._finished;
                    if (!terminal) {
                        double max_quality = choose_action(experience.state_1, &target_net).second;
                        bellman += gamma*max_quality;
                    }

                    target[experience.action.idx] = bellman;
                    policy_net->back_prop(target);
                }
            }
        }

        if (i % 10 == 0) cout << i << endl; 
    }

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<minutes>(end-start);
    cout << "DQL Player " << _id << " training time: " << duration.count() << " minutes.\n";
}

int DQLPlayer::get_move(Game &game) {
    return choose_action(game, &policy_net).first; 
}

#endif