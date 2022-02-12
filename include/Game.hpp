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

#endif