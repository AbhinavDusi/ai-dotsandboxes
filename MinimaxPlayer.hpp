#ifndef MINIMAX_PLAYER_H
#define MINIMAX_PLAYER_H

#include <random>
#include <ctime>

#include "Game.hpp"
#include "Player.hpp"

using namespace std;

typedef struct MinimaxNode {
    int val;
    MinimaxNode() {};
} MinimaxNode; 

class MinimaxPlayer: public Player {
    public:
    MinimaxPlayer(int id) : Player(id) {};
    int move(Game &game);

    private:
    MinimaxNode *construct_tree(MinimaxNode *node, int depth, bool max, Game game);
}; 

MinimaxNode *MinimaxPlayer::construct_tree(MinimaxNode *node, int depth, bool max, Game game) {
    if (node == nullptr) *node = MinimaxNode();

    if (depth == 0) {
        int my_score = game.get_score(_id); 
        int opp_score = game._filled_boxes-my_score;
        node->val = my_score-opp_score;
    } else {

    }

    return node; 
}

int MinimaxPlayer::move(Game &game) {
    construct_tree(nullptr, 3, true, game);

    int scored = game.move(_id, 0); 
    _score += scored;
    return scored;
}

#endif