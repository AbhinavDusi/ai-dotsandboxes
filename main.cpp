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

    if (player1->_score>player2->_score) return player1->_id;
    if (player2->_score<player2->_score) return player2->_id;
    return -1;
}

int main() {
    int N = 1; 
    int w = 0; 
    int l = 0;
    int d = 0; 

    int width = 5;
    int height = 5;
    
    Player *player1 = new DQLPlayer(1, width, height);
    Player *player2 = new RandomPlayer(2); 
    
    for (int i = 0; i < N; i++) {
        int winner;
        if (i%2 == 0) winner = simulate_game(width, height, player1, player2);
        else winner = simulate_game(width, height, player2, player1);

        if (winner==player1->_id) w++;
        if (winner==player2->_id) l++;
        if (winner==-1) d++;
    }
    
    cout << "Wins: " << w << endl;
    cout << "Losses: " << l << endl;
    cout << "Draws: " << d << endl;
    cout << "Total Games Played: " << N << endl;

    return 0; 
}
