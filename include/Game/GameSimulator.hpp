#ifndef GAME_SIMULATOR_H
#define GAME_SIMULATOR_H

#include <unordered_map>

#include "../Player/Player.hpp"
#include "Game.hpp"

using namespace std;

class GameSimulator {
    public:
    static int simulate_game(int width, int height, Player *player1, Player *player2);
    static unordered_map<int, int> simulate_N_games(int N, int width, int height, Player *player1, Player *player2);
};

int GameSimulator::simulate_game(int width, int height, Player *player1, Player *player2) {
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

unordered_map<int, int> GameSimulator::simulate_N_games(int N, int width, int height, Player *player1, Player *player2) {
    int p1 = 0;
    int p2 = 0;
    int d = 0; 

    for (int i = 0; i < N; i++) {
        int winner;
        if (i%2 == 0) winner = GameSimulator::simulate_game(width, height, player1, player2);
        else winner = GameSimulator::simulate_game(width, height, player2, player1);

        if (winner==player1->_id) p1++;
        if (winner==player2->_id) p2++;
        if (winner==-1) d++;
    }

    unordered_map<int, int> scores; 
    scores.insert({1, p1});
    scores.insert({2, p2});
    scores.insert({-1, d});
    return scores;
}

#endif