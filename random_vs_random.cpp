#include <iostream>

#include "Game.hpp"
#include "Player.hpp"
#include "RandomPlayer.hpp"

using namespace std;

int main() {
    RandomPlayer player1();
    RandomPlayer player2();

    Game game(10, 10);
    vector<Move> moves = game._moves; 

    Player current_player = player1; 

    /*
    while (!game._moves.empty()) {
        game.move(current_player.move(moves));

        if (current_player == player1) current_player = player2;
        else current_player = player1;
    }
    */

   game.print();


    return 0;
}