#ifndef MINIMAX_PLAYER_H
#define MINIMAX_PLAYER_H

#include <random>
#include <ctime>

#include "Game.hpp"
#include "Player.hpp"

using namespace std;

typedef struct MinimaxNode {
    int val;
    int move_idx;
    MinimaxNode() {};
} MinimaxNode; 

class MinimaxPlayer: public Player {
    public:
    MinimaxPlayer(int id, int opp_id, int depth): Player(id), _opp_id(opp_id), _depth(depth) {};
    int get_move(Game &game);

    int _opp_id;

    private:
    MinimaxNode construct_tree(int depth, bool maximize, Game game, int alpha, int beta);

    int _depth;
}; 

MinimaxNode MinimaxPlayer::construct_tree(int depth, bool maximize, Game game, int alpha, int beta) {
    MinimaxNode node = MinimaxNode();

    if (depth == 0 || game._finished) {
        node.val = game.get_score(_id)-game.get_score(_opp_id);
        return node; 
    }

    node.val = maximize ? INT_MIN : INT_MAX;
    int curr_id = maximize ? _id : _opp_id;

    for (int i = 0; i < game._moves.size(); i++) {
        Game clone = game.get_clone();
        int scored = clone.move(curr_id, i);
        MinimaxNode child = construct_tree(depth-1, scored ? maximize : !maximize, clone, alpha, beta);

        if (maximize) {
            if (node.val < child.val) {
                node.val = child.val;
                node.move_idx = i; 
            }
            alpha = max(alpha, child.val); 
        } else {
            if (node.val > child.val) {
                node.val = child.val;
                node.move_idx = i; 
            }
            beta = min(beta, child.val); 
        }

        if (beta <= alpha) break;
    }

    return node; 
}

int MinimaxPlayer::get_move(Game &game) {
    if (!game._started) {
        return rng()%game._moves.size();
    } else {
        MinimaxNode root = construct_tree(_depth, true, game.get_clone(), INT_MIN, INT_MAX);
        return root.move_idx;
    }
}

#endif