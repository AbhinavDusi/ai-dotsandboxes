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

void play_games(int width, int height, Hyperparams params, int num_iterations, int N) {
    int p1 = 0, p2 = 0, d = 0;

    for (int j = 0; j < num_iterations; j++) {
        Player *player1 = new DQLPlayer(1, width, height, params);
        Player *player2 = new RandomPlayer(2);

        for (int i = 0; i < N; i++) {
            int winner;
            if (i%2 == 0) winner = simulate_game(width, height, player1, player2);
            else winner = simulate_game(width, height, player2, player1);

            if (winner==player1->_id) p1++;
            if (winner==player2->_id) p2++;
            if (winner==-1) d++;
        }

        cout << ".";   
    }

    cout << "DQL Wins Avg: " << (p1 / (double) num_iterations) << endl;
}

int main() {
    int width = 3, height = 3;

    int dflt_capacity = 20000;
    int dflt_minibatch_size = 16;
    int dflt_episodes = 1000;
    double dflt_alpha = 0.15;
    double dflt_epsilon_0 = 0.99;
    double dflt_epsilon_decay = 0.001;
    double dflt_gamma = 0.9;
    int dflt_update_target = 10;
    int dflt_hidden_layer_size_factor = 2; 

    vector<int> capacity_vals = {10000,20000,40000,80000}; 
    vector<int> minibatch_size_vals = {1,2,4,8,16,32};
    vector<int> episodes_vals = {1000,2000,4000,8000};
    vector<double> alpha_vals = {0.00015,0.0015,0.015,0.15};
    vector<double> epsilon_0_vals = {0.69,0.79,0.89,0.99};
    vector<double> epsilon_decay_vals = {0.001, 0.01, 0.1};
    vector<double> gamma_vals = {0.69,0.79,0.89,0.99};
    vector<double> update_target_vals = {5,10,20,40,80,160};
    vector<double> hidden_layer_size_factor_vals = {1,2,4,8};

    int num_iterations = 20;
    int N = 1000;

    /*
    cout << "Optimizing Capacity" << endl;
    for (int capacity_val : capacity_vals) {
        cout << "Capacity: " << capacity_val;
        Hyperparams params(capacity_val, dflt_minibatch_size, dflt_episodes, dflt_alpha, dflt_epsilon_0,
        dflt_epsilon_decay, dflt_gamma, dflt_update_target, dflt_hidden_layer_size_factor);
        play_games(width, height, params, num_iterations, N);
    }

    cout << "Optimizing Minibatch Size" << endl;
    for (int minibatch_size_val : minibatch_size_vals) {
        cout << "Minibatch Size: " << minibatch_size_val;
        Hyperparams params(dflt_capacity, minibatch_size_val, dflt_episodes, dflt_alpha, dflt_epsilon_0,
        dflt_epsilon_decay, dflt_gamma, dflt_update_target, dflt_hidden_layer_size_factor);
        play_games(width, height, params, num_iterations, N);
    }

    cout << "Optimizing Episodes" << endl;
    for (int episodes_val : episodes_vals) {
        cout << "Episodes: " << episodes_val;
        Hyperparams params(dflt_capacity, dflt_minibatch_size, episodes_val, dflt_alpha, dflt_epsilon_0,
        dflt_epsilon_decay, dflt_gamma, dflt_update_target, dflt_hidden_layer_size_factor);
        play_games(width, height, params, num_iterations, N);
    }

    cout << "Optimizing Alpha" << endl;
    for (double alpha_val : alpha_vals) {
        cout << "Alpha: " << alpha_val;
        Hyperparams params(dflt_capacity, dflt_minibatch_size, dflt_episodes, alpha_val, dflt_epsilon_0,
        dflt_epsilon_decay, dflt_gamma, dflt_update_target, dflt_hidden_layer_size_factor);
        play_games(width, height, params, num_iterations, N);
    }

    cout << "Optimizing Epsilon_0" << endl;
    for (double epsilon_0_val : epsilon_0_vals) {
        cout << "Epsilon_0: " << epsilon_0_val;
        Hyperparams params(dflt_capacity, dflt_minibatch_size, dflt_episodes, dflt_alpha, epsilon_0_val,
        dflt_epsilon_decay, dflt_gamma, dflt_update_target, dflt_hidden_layer_size_factor);
        play_games(width, height, params, num_iterations, N);
    }

    cout << "Optimizing Epsilon Decay" << endl;
    for (double epsilon_decay_val : epsilon_decay_vals) {
        cout << "Epsilon Decay: " << epsilon_decay_val;
        Hyperparams params(dflt_capacity, dflt_minibatch_size, dflt_episodes, dflt_alpha, dflt_epsilon_0,
        epsilon_decay_val, dflt_gamma, dflt_update_target, dflt_hidden_layer_size_factor);
        play_games(width, height, params, num_iterations, N);
    }
    */

    cout << "Optimizing Gamma" << endl;
    for (double gamma_val : gamma_vals) {
        cout << "Gamma: " << gamma_val;
        Hyperparams params(dflt_capacity, dflt_minibatch_size, dflt_episodes, dflt_alpha, dflt_epsilon_0,
        dflt_epsilon_decay, gamma_val, dflt_update_target, dflt_hidden_layer_size_factor);
        play_games(width, height, params, num_iterations, N);
    }

    cout << "Optimizing Update Target" << endl;
    for (int update_target_val : update_target_vals) {
        cout << "Update Target: " << update_target_val;
        Hyperparams params(dflt_capacity, dflt_minibatch_size, dflt_episodes, dflt_alpha, dflt_epsilon_0,
        dflt_epsilon_decay, dflt_gamma, update_target_val, dflt_hidden_layer_size_factor);
        play_games(width, height, params, num_iterations, N);
    }

    cout << "Optimizing Hidden Layer Size Factor" << endl;
    for (int hidden_layer_size_factor_val : hidden_layer_size_factor_vals) {
        cout << "Hidden Layer Size Factor: " << hidden_layer_size_factor_val;
        Hyperparams params(dflt_capacity, dflt_minibatch_size, dflt_episodes, dflt_alpha, dflt_epsilon_0,
        dflt_epsilon_decay, dflt_gamma, dflt_update_target, hidden_layer_size_factor_val);
        play_games(width, height, params, num_iterations, N);
    }

    return 0;
}