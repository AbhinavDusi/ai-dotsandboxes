#include <iostream>

#include "../include/Game.hpp"
#include "../include/Player.hpp"
#include "../include/Random/RandomPlayer.hpp"
#include "../include/Minimax/MinimaxPlayer.hpp"
#include "../include/DQL/DQLPlayer.hpp"
#include "../include/Algorithmic/AlgorithmicPlayer.hpp"
#include "../include/Human/HumanPlayer.hpp"

#define MINIMAX_DEPTH 3

using namespace std;

void assign_player(Player *player, int player_type, int id, int width, int height) {
    if (player_type==0) player = new RandomPlayer(id); 
    if (player_type==1) player = new MinimaxPlayer(id, MINIMAX_DEPTH); 
    if (player_type==2) player = new DQLPlayer(id, width, height); 
    if (player_type==3) player = new AlgorithmicPlayer(id, width, height); 
    if (player_type==4) player = new HumanPlayer(id);
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

    int p1_score = game.get_score(player1->_id);
    int p2_score = game.get_score(player2->_id);

    if (p1_score>p2_score) return player1->_id;
    if (p1_score<p2_score) return player2->_id;
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
    cout << "Random=0; Minimax (depth=3)=1; Deep Q Learning=2; Algorithmic=3; Human=4" << endl;

    cout << "Enter type of Player 1: ";
    cin >> p1_type;
    assign_player(player1, p1_type, 1, width, height);
    
    cout << "Enter type of Player 2: ";
    cin >> p2_type;
    assign_player(player2, p2_type, 2, width, height);
    */

    int width = 4;
    int height = 4;
    int N = 1000;
    
    Player *player1 = new MinimaxPlayer(1, MINIMAX_DEPTH);
    Player *player2 = new MinimaxPlayer(2, MINIMAX_DEPTH);

    //Player *player1 = new RandomPlayer(1); 
    //Player *player2 = new DQLPlayer(2, width, height);

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

    cout << player1->get_name() << " Player 1 average time per move: " 
        << player1->get_avg_move_time() << " microseconds." << endl;
    cout << player2->get_name() << " Player 2 average time per move: " 
        << player2->get_avg_move_time() << " microseconds." << endl;

    return 0; 
}
