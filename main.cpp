#include <iostream>

#include "Game.hpp"
#include "Player.hpp"
#include "RandomPlayer.hpp"
#include "AIPlayer.hpp"

using namespace std;

typedef pair<int, int> Score; 

Score random_vs_random() {
    Game game(5, 5);

    RandomPlayer *player1 = new RandomPlayer(1);
    RandomPlayer *player2 = new RandomPlayer(2);
    Player *current_player = player1; 

    /*
    while (!game._moves.empty()) {
        int scored = current_player.move(game);

        if (scored) continue; 
        if (current_player == player1) current_player = player2;
        else current_player = player1;
    }
    */

    game.print();

    return make_pair(player1->_score, player2->_score);
}

int main() {
    Score score = random_vs_random();

    return 0; 
}