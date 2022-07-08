#ifndef ALGORITHMIC_PLAYER_H
#define ALGORITHMIC_PLAYER_H

#include "../../Game/Game.hpp"
#include "../Player.hpp"

using namespace std;

typedef pair<int, int> Box;
typedef vector<Box> Chain;

class AlgorithmicPlayer: public Player {
    public:
    AlgorithmicPlayer(int id): Player(id) {};
    int get_move(Game &game); 
    string get_name() { return "Algorithmic"; }

    private:
    int num_surrounding_lines(Game &game, int x, int y) const;
    Chain get_chain(Game &game, Box b) const; 
    vector<Chain> get_no_chains(Game &game) const;
    vector<Chain> get_open_chains(Game &game) const;
    vector<Chain> get_closed_chains(Game &game) const;
    vector<vector<Chain>> get_chains(Game &game) const;
}; 

int AlgorithmicPlayer::num_surrounding_lines(Game &game, int x, int y) const {
    GameImage game_image = game._game_image;
    return game_image[x][y][0]+game_image[x][y][1]+game_image[x][y][2]+game_image[x][y][3];
}

Chain AlgorithmicPlayer::get_chain(Game &game, Box b) const {
    Chain v; 
    return v;
}

vector<Chain> AlgorithmicPlayer::get_no_chains(Game &game) const {
    vector<Chain> v; 

    GameImage game_image = game._game_image;
    for (int x = 0; x < game._height; x++) {
        for (int y = 0; y < game._width; y++) {
            if (num_surrounding_lines(game, x, y) <= 1) {
                Chain c;
                c.push_back(make_pair(x, y));
                v.push_back(c);
            }
        }
    }

    return v; 
}

vector<Chain> AlgorithmicPlayer::get_open_chains(Game &game) const {
    vector<Chain> v; 
    return v; 
}

vector<Chain> AlgorithmicPlayer::get_closed_chains(Game &game) const {
    vector<Chain> v; 
    return v;
}

vector<vector<Chain>> AlgorithmicPlayer::get_chains(Game &game) const {
    vector<vector<Chain>> v; 
    v.push_back(get_no_chains(game));
    v.push_back(get_open_chains(game));
    v.push_back(get_closed_chains(game));
    return v;
}

int AlgorithmicPlayer::get_move(Game &game) {
    game.print();

    vector<Move> moves = game._moves;

    auto chains = get_chains(game);

    cout << "No chains: ";
    vector<Chain> no_chains = chains[0];
    for (Chain c : no_chains) {
        for (Box b : c) {
            cout << "(" << b.first << ", " << b.second << ")";
        }
    }
    cout << endl;

    if (chains[0].empty()) { // Only chains remaining

    } else { // Non-chained boxes remaining

    }
    
    return 0;
}

#endif