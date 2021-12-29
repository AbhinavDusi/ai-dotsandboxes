#include <iostream>

#include "Game.hpp"
#include "Player.hpp"
#include "RandomPlayer.hpp"
#include "MinimaxPlayer.hpp"
#include "DQLPlayer.hpp"

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
    /*
    int w = 0; 
    int l = 0;
    int d = 0; 
    

    for (int i = 0; i < 100; i++) {
        int mvr = simulate_game(6, 6, new MinimaxPlayer(1, 2, 2), new MinimaxPlayer(2, 1, 4));
        if (mvr == 1) w++;
        if (mvr == 2) l++;
        if (mvr == 0) d++;
    }

    cout << "Wins: " << w << endl;
    cout << "Losses: " << l << endl;
    cout << "Draws: " << d << endl;
    */

   Game game(5, 5); 
   DRLPlayer player1(1, game);

    return 0; 
}