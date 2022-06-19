#include "../Game.hpp"
#include "../Player.hpp"
#include "../Random/RandomPlayer.hpp"
#include "../DQL/DQLPlayer.hpp"

#include <vector>

using namespace std;

int simulate_game(int width, int height, Player *player1, Player *player2) {
    Game game(width, height);
    Player *current_player = player1; 

    while (!game._finished) {
        int scored = current_player->move(game);
        if (scored) continue; 
        if (current_player == player1) current_player = player2;
        else current_player = player1;
    }

    int p1_score = game.get_score(player1->_id);
    int p2_score = game.get_score(player2->_id);

    if (p1_score>p2_score) return player1->_id;
    if (p1_score<p2_score) return player2->_id;
    return -1;
}

int main() {
    int width = 4, height = 4;

    int dflt_capacity = 20000;
    int dflt_minibatch_size = 16;
    int dflt_episodes = 1000;
    double dflt_alpha = 0.15;
    double dlft_epsilon_0 = 0.99;
    double dflt_epsilon_decay = 0.001;
    double dflt_gamma = 0.9;
    int dflt_update_target = 10;
    int dflt_hidden_layer_size_factor = 2; 

    vector<int> capacity_vals = {10000,20000,40000,80000}; 
    vector<int> minibatch_size_vals = {1,2,4,8,16,32};
    vector<int> episodes_vals = {1000,2000,4000,8000};
    vector<double> alpha_vals = {0.00015,0.0015,0.015,0.15};
    vector<double> epsilon_0_vals = {0.69,0.79,0.89,0.99};
    vector<double> gamma_vals = {0.69,0.79,0.89,0.99};
    vector<double> update_target_vals = {5,10,20,40,80,160};
    vector<double> hidden_layer_size_factor_vals = {1,2,4,8};

    int num_iteratons = 10;

    return 0;
}