#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std; 

typedef vector<vector<vector<double>>> GameImage; 

typedef struct Move {
    int row, col, direction;
    Move(int row, int col, int direction): row(row), col(col), direction(direction) {};
} Move; 

class Game {
    public:
    Game(int width, int height); 
    Game() {};
    Game get_clone() const;
    int move(int player_id, int move_idx);
    int get_score(int player_id) const;
    void print();
    static Game get_random_game(int width, int height); 
    bool _started;
    bool _finished; 
    int _width;
    int _height;
    vector<Move> _moves; 

    private: 
    GameImage _game_image;
    unordered_map<int, int> _score;
};

Game::Game(int width, int height): _finished(false), _started(false), _width(width), _height(height) {
    _game_image = vector<vector<vector<double>>>(height, vector<vector<double>>(width, vector<double>(5)));

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            _moves.push_back(Move(i, j, 0)); 
            _moves.push_back(Move(i, j, 1)); 
            _moves.push_back(Move(i, j, 2)); 
            _moves.push_back(Move(i, j, 3)); 
        }
    }
}

Game Game::get_clone() const {
    Game game;
    game._finished = _finished;
    game._moves = _moves;
    game._game_image = _game_image;
    game._started = _started;
    return game;
}

int Game::get_score(int player_id) const {
    if (_score.find(player_id)==_score.end()) return 0;
    return _score.at(player_id);
}

int Game::move(int player_id, int move_idx) {
    _started = true;
    if (_finished) return -1; 

    int prev_score = get_score(player_id); 

    Move move = _moves[move_idx]; 
    _moves.erase(_moves.begin()+move_idx);

    if (move.direction==0) {

    }
    if (move.direction==1) {
        
    }
    if (move.direction==2) {
        
    }
    if (move.direction==3) {
        
    }
    /*
    if (move.direction == 0) {
        _board[2*move.row+1][2*move.col] = '|';
    } else {
        _board[2*move.row][2*move.col+1] = '-';
    }
    */

    int next_score = get_score(player_id);

    if (_moves.empty()) _finished = true; 

    return next_score-prev_score;
}

void Game::print() {
    vector<vector<char>> board(2*_height+1, vector<char>(2*_width+1));

    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board.front().size(); j++) {
            if (i%2==0 && j%2==0) board[i][j] = '*';
            else board[i][j] = ' ';
        }
    }

    for (int i = 0; i < _height; i++) {
        for (int j = 0; j < _width; j++) {
            if (_game_image[i][j][0]) board[2*i][2*j+1] = '-';
            if (_game_image[i][j][1]) board[2*i+1][2*j+2] = '|';
            if (_game_image[i][j][2]) board[2*i+2][2*j+1] = '-';
            if (_game_image[i][j][3]) board[2*i+1][2*j] = '|';
            if (_game_image[i][j][4]) board[2*i+1][2*j+1] = _game_image[i][j][4]+48;
        }
    }

    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board.front().size(); j++) {
            cout << board[i][j];
        }
        cout << "\n";
    }
}

#endif