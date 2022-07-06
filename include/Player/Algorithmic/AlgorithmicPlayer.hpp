#ifndef ALGORITHMIC_PLAYER_H
#define ALGORITHMIC_PLAYER_H

#include "../../Game/Game.hpp"
#include "../Player.hpp"

using namespace std;

class AlgorithmicPlayer: public Player {
    public:
    AlgorithmicPlayer(int id): Player(id) {};
    int get_move(Game& game); 
    string get_name() { return "Algorithmic"; }

    private:
    int _width;
    int _height;
    bool _first_to_move;
}; 

int AlgorithmicPlayer::get_move(Game &game) {
    GameImage game_image = game._game_image;
    
    return 0;
}

#endif