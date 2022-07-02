#ifndef DQL_ENSEMBLE_H
#define DQL_ENSEMBLE_H

#include <vector>
#include <unordered_map>

#include "DQLPlayer.hpp"
#include "../Player.hpp"
#include "../../Game/Game.hpp"
#include "../../Game/GameSimulator.hpp"
#include "../Random/RandomPlayer.hpp"

using namespace std;

class DQLEnsemble: public Player {
    public:
    DQLEnsemble(int id, int N, int width, int height, Hyperparams &params);    
    int get_move(Game &game); 
    string get_name() { return "Deep Q Learning Ensemble"; };

    private:
    vector<DQLPlayer *> ensemble;
    vector<double> weights;
};

DQLEnsemble::DQLEnsemble(int id, int N, int width, int height, Hyperparams &params): Player(id) {
    auto start = high_resolution_clock::now();

    for (int i = 0; i < N; i++) {
        ensemble.push_back(new DQLPlayer(1, width, height, params));

        DQLPlayer *dql = ensemble.back();
        RandomPlayer *random = new RandomPlayer(2);

        int per_iteration = 1000;
        unordered_map<int, int> scores = GameSimulator::simulate_N_games(per_iteration, width, height, dql, random);
        int dql_wins = scores.at(dql->_id);

        weights.push_back(dql_wins/(double) per_iteration);
    }

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<minutes>(end-start);
    cout << get_name() << " " << _id << " training time: " << duration.count() << " minutes.\n";
}

int DQLEnsemble::get_move(Game &game) {
    unordered_map<int, double> votes;
    int best_move = 0; 
    int highest_votes = 0;
    for (int i = 0; i < ensemble.size(); i++) {
        int move = ensemble[i]->get_move(game);

        if (!votes.count(move)) votes.insert({move, 0});
        votes.at(move)+=weights[i];
        
        if (votes.at(move) > highest_votes) {
            highest_votes = votes.at(move);
            best_move = move;
        }
    }

    return best_move;
}

#endif