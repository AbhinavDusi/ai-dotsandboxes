#ifndef DQL_PLAYER_H
#define DQL_PLAYER_H

#include <vector>

#include "../Game.hpp"
#include "../Player.hpp"
#include "NeuralNet.hpp"
#include "ReplayMemory.hpp"

#include <fstream>
#include <chrono>

#include "../Random/RandomPlayer.hpp"

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
    return make_pair(action, max_quality);
}

void DQLPlayer::exp_decay(double *x, double x_0, double decay, int n) {
    *x = x_0*exp(-1*decay*n);
}    

DQLPlayer::DQLPlayer(int id, int width, int height): Player(id) {
    auto start = high_resolution_clock::now();

    int capacity = 100000;
    ReplayMemory rm(capacity);

    int minibatch_size = 64;

    // Tradeoff between num episodes and num neurons in hidden layers?
    int episodes = 1000; 
    bool wins[episodes];

    double alpha = 0.15;

    double epsilon_0 = 0.99;
    double epsilon = epsilon_0;
    double epsilon_decay = 0.001;

    double gamma = 0.9;

    int update_target = 10;

    int layer_size = 4*width*height;
    vector<int> topology; 
    topology.push_back(layer_size);
    topology.push_back(4*layer_size);
    topology.push_back(4*layer_size);
    topology.push_back(layer_size);

    policy_net = new NeuralNet(topology, alpha);
    target_net = new NeuralNet(topology, alpha);

    for (int i = 0; i < episodes; i++) {
        if (i%update_target==0) policy_net->load(*target_net);

        exp_decay(&epsilon, epsilon_0, epsilon_decay, i);

        Game game_0(width, height);

        while (!game_0._finished) {
            bool explore = (double) rng()/rng.max() > epsilon; 
            int action_idx = 0;
            if (explore) action_idx = rng()%game_0._moves.size();
            else action_idx = choose_action(game_0, &target_net).first;
            Move action = game_0._moves[action_idx];
        
            Game game_1 = game_0;

            double reward = game_1.move(_id, action_idx);
            
            rm.add_experience(Experience(game_0, action, reward, game_1));

            game_0 = game_1;

            if (rm.can_provide_sample(minibatch_size)) {
                vector<Experience> sample = rm.get_sample(minibatch_size);
                for (int j = 0; j < minibatch_size; j++) {
                    Experience experience = sample[j]; 

                    double bellman = experience.reward;
                    
                    bool terminal = experience.state_1._finished;
                    if (!terminal) {
                        double max_quality = choose_action(experience.state_1, &target_net).second;
                        bellman += gamma*max_quality;
                    }

                    policy_net->feed_forward(flatten_game_image(experience.state_0));
                    vector<double> result = policy_net->get_result();
                    vector<double> target = result;

                    target[experience.action.idx] = bellman;
                    policy_net->back_prop(target);
                }
            }
        }

        Game game(width, height);
        RandomPlayer *opp = new RandomPlayer(3);
        bool my_turn = false;

        while (!game._finished) {
            int scored = 0; 
            if (my_turn) {
                scored = move(game);
            } else {
                scored = opp->move(game);
            }
            if (scored) continue; 

            my_turn = !my_turn;
        }

        int won = game.get_score(_id) > game.get_score(opp->_id);
        wins[i] = won;
        
        if (i%10 == 0 && i>=10) {
            int num_wins = 0; 
            for (int j = i-10; j < i; j++) {
                if (wins[j]) {
                    num_wins++;
                }
            }
            cout << "Episode " << i << ": " << num_wins << "\n";
        }
    }

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<minutes>(end-start);
    cout << "DQL Player " << _id << " training time: " << duration.count() << " minutes.\n";
}

int DQLPlayer::get_move(Game &game) {
    return choose_action(game, &policy_net).first;
}

#endif
