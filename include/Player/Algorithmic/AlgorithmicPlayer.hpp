#ifndef ALGORITHMIC_PLAYER_H
#define ALGORITHMIC_PLAYER_H

#include "../../Game/Game.hpp"
#include "../Player.hpp"

using namespace std;

class AlgorithmicPlayer: public Player {
    public:
    AlgorithmicPlayer(int id): Player(id) {};
    int get_move(Game &game); 
    string get_name() { return "Algorithmic"; }

    private:
    vector<vector<pair<int, int>>> get_open_chains(Game &game) const;
    vector<vector<pair<int, int>>> get_closed_chains(Game &game) const;
}; 

vector<vector<pair<int, int>>> AlgorithmicPlayer::get_open_chains(Game &game) const {

}

vector<vector<pair<int, int>>> AlgorithmicPlayer::get_closed_chains(Game &game) const {

}

int AlgorithmicPlayer::get_move(Game &game) {
    vector<Move> moves = game._moves;

    vector<vector<pair<int, int>>> open_chains = get_open_chains(game);
    vector<vector<pair<int, int>>> closed_chains = get_closed_chains(game);

    int total_chained_boxes = 0; 
    for (vector<pair<int, int>> v : open_chains) total_chained_boxes += v.size();
    for (vector<pair<int, int>> v : closed_chains) total_chained_boxes += v.size();
    bool only_chains = total_chained_boxes == game._width * game._height;
    
    return 0;
}

#endif