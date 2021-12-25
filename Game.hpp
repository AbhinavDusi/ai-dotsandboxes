#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>

using namespace std; 

typedef vector<vector<char>> Board; 

typedef struct Move {
    int row, col, direction;
    Move(int row, int col, int direction): row(row), col(col), direction(direction) {}
} Move; 

class Game {
    public:
    Game(int width, int height); 
    Game() {};
    Game get_clone() const;
    int move(int player_id, int move_idx);
    int get_score(int player_id) const;
    void print();

    bool _finished; 
    bool _started;
    vector<Move> _moves; 

    private: 
    void fill_boxes(int player_id); 

    Board _board;
};

Game::Game(int width, int height): _finished(false), _started(false) {
    for (int i = 0; i < 2*height-1; i++) {
        _board.push_back(vector<char>()); 
        for (int j = 0; j < 2*width-1; j++) {
            if (i%2==0 && j%2==0) _board.back().push_back('*');
            else _board.back().push_back(' ');
        }
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (i != height-1) _moves.push_back(Move(i, j, 0));
            if (j != width-1) _moves.push_back(Move(i, j, 1));
        }
    }
}

Game Game::get_clone() const {
    Game game;
    game._finished = _finished;
    game._moves = _moves;
    game._board = _board;
    game._started = _started;
    return game;
}

void Game::fill_boxes(int player_id) {
    for (int i = 0; i < _board.size(); i++) {
        for (int j = 0; j < _board.front().size(); j++) {
            if (
                i%2==1 && j%2==1 && _board[i][j]==' '
                && _board[i+1][j]=='-'
                && _board[i-1][j]=='-'
                && _board[i][j+1]=='|'
                && _board[i][j-1]=='|'
            ) {
                _board[i][j] = player_id+48;
            }
        }
    }
}

int Game::get_score(int player_id) const {
    int count = 0; 
    
    for (int i = 0; i < _board.size(); i++) {
        for (int j = 0; j < _board.front().size(); j++) {
            if (_board[i][j]==player_id+48) {
                count++; 
            }
        }
    }

    return count; 
}

int Game::move(int player_id, int move_idx) {
    _started = true;
    if (_finished) return 0; 

    int prev_score = get_score(player_id); 

    Move move = _moves[move_idx]; 
    _moves.erase(_moves.begin()+move_idx);

    if (move.direction == 0) {
        _board[2*move.row+1][2*move.col] = '|';
    } else {
        _board[2*move.row][2*move.col+1] = '-';
    }

    fill_boxes(player_id);
    int next_score = get_score(player_id);

    if (_moves.empty()) _finished = true; 

    return next_score-prev_score;
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