#ifndef ALGORITHMIC_PLAYER_H
#define ALGORITHMIC_PLAYER_H

#include "Game.hpp"
#include "Player.hpp"

using namespace std;

class AlgorithmicPlayer: public Player {
    public:
    AlgorithmicPlayer(int id, int width, int height): 
        Player(id), _width(width), _height(height), _first_to_move(id == 1) {};
    int get_move(Game& game); 
    string get_name() { return "Algorithmic"; }

    private:
    int _width;
    int _height;
    bool _first_to_move;
}; 

int AlgorithmicPlayer::get_move(Game &game) {
    bool odd_chains = _first_to_move && (_width%2==0) && (_height%2==0); 
    return 0;
}

#endif