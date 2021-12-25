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
    MinimaxPlayer(int id, int opp_id, int depth): Player(id), _opp_id(opp_id), _depth(depth) {};
    int move(Game &game);
    int _opp_id;

    private:
    MinimaxNode construct_tree(int depth, bool max, Game game);

    int _depth;
}; 

MinimaxNode MinimaxPlayer::construct_tree(int depth, bool max, Game game) {
    MinimaxNode node = MinimaxNode();

    if (depth == 0 || game._finished) {
        node.val = game.get_score(_id)-game.get_score(_opp_id);
        return node; 
    }

    node.val = max ? INT_MIN : INT_MAX;
    int curr_id = max ? _id : _opp_id;

    for (int i = 0; i < game._moves.size(); i++) {
        Game clone = game.get_clone();
        clone.move(curr_id, i);
        MinimaxNode child = construct_tree(depth-1, !max, clone);

        if (max) node.val = std::max(node.val, child.val);
        else node.val = min(node.val, child.val);
    }

    return node; 
}

int MinimaxPlayer::move(Game &game) {
    MinimaxNode root = construct_tree(_depth, true, game.get_clone());

    int scored = game.move(_id, 0); 
    _score += scored;
    return scored;
}

#endif