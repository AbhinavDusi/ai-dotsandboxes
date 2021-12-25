#include <iostream>

#include "Game.hpp"
#include "Player.hpp"
#include "RandomPlayer.hpp"
#include "MinimaxPlayer.hpp"

using namespace std;

int simulate_game(int width, int height, Player *player1, Player *player2) {
    Game game(width, height);
    Player *current_player = player1; 

    while (!game._finished) {
        int scored = current_player->move(game);

        if (scored) continue; 
        if (current_player == player1) current_player = player2;
        else current_player = player1;
    }

    if (player1->_score > player2->_score) return player1->_id;
    if (player1->_score < player2->_score) return player2->_id;  
    return 0; 
}

int main() {
    //int rvr = simulate_game(5, 5, new RandomPlayer(1), new RandomPlayer(2));
    int mvr = simulate_game(5, 5, new MinimaxPlayer(1), new RandomPlayer(2));

    return 0; 
}