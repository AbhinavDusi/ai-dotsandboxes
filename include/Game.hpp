#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std; 

typedef vector<vector<vector<int>>> GameImage; 

typedef struct Move {
    int row, col, direction, idx;
    Move(int row, int col, int direction, int idx): 
        row(row), col(col), direction(direction), idx(idx) {};
    Move() {};
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
    GameImage _game_image;

    private: 
    bool completed_box(int row, int col);
    unordered_map<int, int> _score;
};

Game::Game(int width, int height): _finished(false), _started(false), _width(width), _height(height) {
    _game_image = vector<vector<vector<int>>>(height, vector<vector<int>>(width, vector<int>(5)));

    int idx = 0;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            _moves.push_back(Move(i, j, 0, idx++)); 
            _moves.push_back(Move(i, j, 1, idx++)); 
            _moves.push_back(Move(i, j, 2, idx++)); 
            _moves.push_back(Move(i, j, 3, idx++)); 
        }
    }
}

Game Game::get_clone() const {
    Game game;
    game._finished = _finished;
    game._moves = _moves;
    game._game_image = _game_image;
    game._started = _started;
    game._height = _height;
    game._width = _width;
    return game;
}

int Game::get_score(int player_id) const {
    if (_score.find(player_id)==_score.end()) return 0;
    return _score.at(player_id);
}

bool Game::completed_box(int row, int col) {
    return _game_image[row][col][0]
        &&_game_image[row][col][1]
        &&_game_image[row][col][2]
        &&_game_image[row][col][3];
}

int Game::move(int player_id, int move_idx) {
    _started = true;
    if (_finished) return -1; 

    int scored = 0;

    Move move = _moves[move_idx]; 
    _moves.erase(_moves.begin()+move_idx);
    _game_image[move.row][move.col][move.direction] = 1;
    if (completed_box(move.row, move.col)) {
        scored++;
        _game_image[move.row][move.col][4] = player_id;
    }

    int other_row = -1, other_col = -1, other_direction = -1;
    if (move.direction==0) {
        other_row = move.row-1;
        other_col = move.col;
        other_direction = 2;
    }
    if (move.direction==1) {
        other_row = move.row;
        other_col = move.col+1;
        other_direction = 3;
    }
    if (move.direction==2) {
        other_row = move.row+1;
        other_col = move.col;
        other_direction = 0;
    }
    if (move.direction==3) {
        other_row = move.row;
        other_col = move.col-1;
        other_direction = 1;
    }

    int other_move_idx = -1;
    for (int i = 0; i < _moves.size(); i++) {
        if (_moves[i].col==other_col
            &&_moves[i].row==other_row
            &&_moves[i].direction==other_direction) {
            other_move_idx = i;
        }
    }
    
    if (other_move_idx!=-1) {
        Move other_move = _moves[other_move_idx];
        _moves.erase(_moves.begin()+other_move_idx);

        _game_image[other_move.row][other_move.col][other_move.direction] = 1;
        if (completed_box(other_move.row, other_move.col)) {
            scored++;
            _game_image[other_move.row][other_move.col][4] = player_id;
        }
    }

    if (_moves.empty()) _finished = true; 

    if (_score.find(player_id)==_score.end()) _score[player_id] = 0;
    _score[player_id] += scored;

    return scored;
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