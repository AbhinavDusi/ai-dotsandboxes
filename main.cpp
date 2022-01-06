#include <iostream>

#include "Game.hpp"
#include "Player.hpp"
#include "RandomPlayer.hpp"
#include "MinimaxPlayer.hpp"
#include "DQLPlayer.hpp"

using namespace std;

pair<int, int> simulate_game(int width, int height, Player *player1, Player *player2) {
    Game game(width, height);
    Player *current_player = player1; 

    while (!game._finished) {
        int scored = current_player->move(game);

        if (scored) continue; 
        if (current_player == player1) current_player = player2;
        else current_player = player1;
    }
    
    return make_pair(player1->score, player2->score); 
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
        pair<int, int> score; 
        if (i%2 == 0) score = simulate_game(width, height, player1, player2);
        else score = simulate_game(width, height, player2, player1);
        if (score.first>score.second) w++;
        if (score.first<score.second) l++;
        if (score.first==score.second) d++;
    }
    
    cout << "Wins: " << w << endl;
    cout << "Losses: " << l << endl;
    cout << "Draws: " << d << endl;
    cout << "Total Games Played: " << N << endl;

    return 0; 
}
