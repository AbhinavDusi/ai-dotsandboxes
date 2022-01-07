#include <iostream>

#include "Game.hpp"
#include "Player.hpp"
#include "RandomPlayer.hpp"
#include "MinimaxPlayer.hpp"
#include "DQLPlayer.hpp"
#include "AlgorithmicPlayer.hpp"

using namespace std;

void assign_player(Player *player, int player_type, int id, int opp_id, int depth, int width, int height) {
    if (player_type==0) player = new RandomPlayer(id); 
    if (player_type==1) player = new MinimaxPlayer(id, opp_id, depth); 
    if (player_type==2) player = new DQLPlayer(id, width, height); 
    if (player_type==3) player = new AlgorithmicPlayer(id); 
}

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
    if (player1->_score<player2->_score) return player2->_id;
    return -1;
}

int main() {
    /*
    int width, height, N;
    cout << "Enter the width and height separated by a space: ";
    cin >> width >> height;
    cout << "Enter the number of games to simulate: ";
    cin >> N; 

    Player *player1, player2;
    int p1_type, p2_type;
    cout << "Random=0; Minimax=1; Deep Q Learning=2; Algorithmic=3." << endl;

    cout << "Enter type of Player 1: ";
    cin >> p1_type;
    assign_player(player1, p1_type, 1, 2, 3, width, height);

    cout << "Enter type of Player 2: ";
    cin >> p2_type;
    assign_player(player2, p2_type, 2, 1, 3, width, height);
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

    /*
    cout << player1->get_name() << " Player 1 average time per move: " << p1->get_avg_move_time() << endl;
    cout << player2->get_name() << " Player 2 average time per move: " << p2->get_avg_move_time() << endl;
    */

    return 0; 
}
