#include <iostream>

#include "Game.hpp"
#include "Player.hpp"
#include "RandomPlayer.hpp"
#include "AIPlayer.hpp"

using namespace std;

int random_vs_random() {
    Game game(5, 5);

    RandomPlayer *player1 = new RandomPlayer(1);
    RandomPlayer *player2 = new RandomPlayer(2);
    Player *current_player = player1; 

    /*
    while (!game._finished) {
        int scored = current_player->move(game);

        if (scored) continue; 
        if (current_player == player1) current_player = player2;
        else current_player = player1;
    }
    */

    game.print();

    if (player1->_score > player2->_score) return 1;
    if (player1->_score < player2->_score) return 2;  
    return 0; 
}

int main() {
    int result = random_vs_random();

    return 0; 
}