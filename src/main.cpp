#include <iostream>

#include "../include/Game/Game.hpp"
#include "../include/Game/GameSimulator.hpp"
#include "../include/Player.hpp"
#include "../include/Random/RandomPlayer.hpp"
#include "../include/Minimax/MinimaxPlayer.hpp"
#include "../include/DQL/DQLPlayer.hpp"
#include "../include/Algorithmic/AlgorithmicPlayer.hpp"
#include "../include/Human/HumanPlayer.hpp"

int MINIMAX_DEPTH = 3;

Hyperparams DQL_PARAMS(5000, 8, 1000, 0.15, 0.94, 0.001, 0.89, 1, 2);
int DQL_NUM_TO_CREATE = 30;
int DQL_PER_ITERATION = 1000;

using namespace std;

void assign_player(Player *player, int player_type, int id, int width, int height) {
    if (player_type==0) player = new RandomPlayer(id); 
    if (player_type==1) player = new MinimaxPlayer(id, MINIMAX_DEPTH); 
    if (player_type==2) player = new DQLPlayer(id, width, height, DQL_PARAMS); 
    if (player_type==3) player = new AlgorithmicPlayer(id, width, height); 
    if (player_type==4) player = new HumanPlayer(id);
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

    int width = 3;
    int height = 3;
    int N = 1000;

    Player *player1 = new DQLPlayer(1, width, height, DQL_NUM_TO_CREATE, DQL_PER_ITERATION, DQL_PARAMS);
    Player *player2 = new RandomPlayer(2);
    //Player *player2 = new MinimaxPlayer(2, MINIMAX_DEPTH);

    unordered_map<int, int> scores = GameSimulator::simulate_N_games(N, width, height, player1, player2); 
    int p1 = scores.at(player1->_id);
    int p2 = scores.at(player2->_id);
    int d = scores.at(-1);
    
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
