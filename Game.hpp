#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>

using namespace std; 

typedef vector<vector<char>> Board; 

typedef struct Move {
    int r1, c1, r2, c2;
} Move; 

class Game {
    public:
    Game(int width, int height); 
    int move(int player_id, int move_idx);
    void print();

    bool _finished; 
    vector<Move> _moves; 

    private: 
    Board _board;
};

Game::Game(int width, int height) {
    _finished = false; 

    for (int i = 0; i < 2*height-1; i++) {
        _board.push_back(vector<char>()); 
        for (int j = 0; j < 2*width-1; j++) {
            if (i%2==0 && j%2==0) _board.back().push_back('*');
            else _board.back().push_back(' ');
        }
    }
}

int Game::move(int player_id, int move_idx) {
    if (_finished) return 0; 

    Move move = _moves[move_idx]; 
    _moves.erase(_moves.begin()+move_idx);

    if (_moves.size() == 0) {
        _finished = true; 
    }

    return 0;
}

void Game::print() {
    for (int i = 0; i < _board.size(); i++) {
        for (int j = 0; j < _board.front().size(); j++) {
            cout << _board[i][j];
        }
        cout << "\n";
    }
}

#endif