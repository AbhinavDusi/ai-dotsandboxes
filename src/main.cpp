#include <iostream>

#include "../include/Game/Game.hpp"
#include "../include/Game/GameSimulator.hpp"
#include "../include/Player/Player.hpp"
#include "../include/Player/Random/RandomPlayer.hpp"
#include "../include/Player/Minimax/MinimaxPlayer.hpp"
#include "../include/Player/DQL/DQLEnsemble.hpp"
#include "../include/Player/Algorithmic/AlgorithmicPlayer.hpp"
#include "../include/Player/Human/HumanPlayer.hpp"

using namespace std;

int MINIMAX_DEPTH = 3;

Hyperparams DQL_PARAMS(5000, 8, 1000, 0.15, 0.94, 0.001, 0.89, 1, 2);
int DQL_NUM_TO_CREATE = 25;

void assign_player(Player *player, int player_type, int id, int width, int height) {
    if (player_type==0) player = new RandomPlayer(id); 
    if (player_type==1) player = new MinimaxPlayer(id, MINIMAX_DEPTH); 
    if (player_type==2) player = new DQLEnsemble(id, width, height, DQL_NUM_TO_CREATE, DQL_PARAMS); 
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
    cout << "Random=0; Minimax (depth=3)=1; Deep Q Learning Ensemble=2; Algorithmic=3; Human=4" << endl;

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

    //Player *player2 = new MinimaxPlayer(2, MINIMAX_DEPTH);

    for (int i = 0; i < 9; i++) {
        Player *player1 = new DQLEnsemble(1, 25, width, height, DQL_PARAMS);
        Player *player2 = new RandomPlayer(2);

        unordered_map<int, int> scores = GameSimulator::simulate_N_games(N, width, height, player1, player2); 
        int p1 = scores.at(player1->_id);
        int p2 = scores.at(player2->_id);
        int d = scores.at(-1);

        cout << p1 << endl;
    }
    
    /*
    cout << player1->get_name() << " Player 1 wins: " << p1 << endl;
    cout << player2->get_name() << " Player 2 wins: " << p2 << endl;
    if (width*height % 2 == 0) cout << "Draws: " << d << endl;
    cout << "Total Games Played: " << N << endl;

    cout << player1->get_name() << " Player 1 average time per move: " 
        << player1->get_avg_move_time() << " microseconds." << endl;
    cout << player2->get_name() << " Player 2 average time per move: " 
        << player2->get_avg_move_time() << " microseconds." << endl;
    */

    return 0; 
}
