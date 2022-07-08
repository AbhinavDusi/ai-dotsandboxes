#ifndef ALGORITHMIC_PLAYER_H
#define ALGORITHMIC_PLAYER_H

#include "../../Game/Game.hpp"
#include "../Player.hpp"

using namespace std;

typedef pair<int, int> Box;

class AlgorithmicPlayer: public Player {
    public:
    AlgorithmicPlayer(int id): Player(id) {};
    int get_move(Game &game); 
    string get_name() { return "Algorithmic"; }

    private:
    vector<Box> get_chain(Game &game, Box b) const; 
    vector<vector<Box>> get_no_chains(Game &game) const;
    vector<vector<Box>> get_open_chains(Game &game) const;
    vector<vector<Box>> get_closed_chains(Game &game) const;
    vector<vector<vector<Box>>> get_chains(Game &game) const;
}; 

vector<Box> AlgorithmicPlayer::get_chain(Game &game, Box b) const {
    vector<Box> v; 
    return v;
}

vector<vector<Box>> AlgorithmicPlayer::get_no_chains(Game &game) const {
    vector<vector<Box>> v; 
    return v; 
}

vector<vector<Box>> AlgorithmicPlayer::get_open_chains(Game &game) const {
    vector<vector<Box>> v; 
    return v; 
}

vector<vector<Box>> AlgorithmicPlayer::get_closed_chains(Game &game) const {
    vector<vector<Box>> v; 
    return v;
}

vector<vector<vector<Box>>> AlgorithmicPlayer::get_chains(Game &game) const {
    vector<vector<vector<Box>>> v; 
    v.push_back(get_no_chains(game));
    v.push_back(get_open_chains(game));
    v.push_back(get_closed_chains(game));
    return v;
}

int AlgorithmicPlayer::get_move(Game &game) {
    game.print();

    vector<Move> moves = game._moves;

    auto chains = get_chains(game);

    if (chains[0].empty()) {

    } else {

    }
    
    return 0;
}

#endif