#include <iostream>

#include "Game.hpp"
#include "RandomPlayer.hpp"

using namespace std;

int main() {
    Game game(10, 10);

    RandomPlayer player1(); 
    RandomPlayer player2();

    vector<Move> moves = game._moves; 

    /*
    while (!game._moves.empty()) {

    }
    */

   cout << game._moves.size();


    return 0;
}