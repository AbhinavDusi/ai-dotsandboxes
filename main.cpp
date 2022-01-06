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
    /*
    int width, height, N;
    cout << "Enter the width and height separated by a space: ";
    cin >> width >> height;
    cout << "Enter the number of games to simulate: ";
    cin >> N; 

    cout << "Random=0; Minimax=1; Deep Q Learning=2; Algorithmic=3.";
    cout << "Enter type of Player 1: ";
    cout << "Enter type of Player 2: ";
    */

    int width = 5;
    int height = 5;
    int N = 1;
    
    Player *player1 = new DQLPlayer(1, width, height);
    Player *player2 = new RandomPlayer(2); 

    int p1 = 0; 
    int p2 = 0;
    int d = 0; 
    
    for (int i = 0; i < N; i++) {
        int winner;
        if (i%2 == 0) winner = simulate_game(width, height, player1, player2);
        else winner = simulate_game(width, height, player2, player1);

        if (winner==player1->_id) p1++;
        if (winner==player2->_id) p2++;
        if (winner==-1) d++;
    }
    
    cout << player1->get_name() << " Player 1 wins: " << p1 << endl;
    cout << player2->get_name() << " Player 2 wins: " << p2 << endl;
    cout << "Draws: " << d << endl;
    cout << "Total Games Played: " << N << endl;

    return 0; 
}
