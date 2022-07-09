#ifndef ALGORITHMIC_PLAYER_H
#define ALGORITHMIC_PLAYER_H

#include "../../Game/Game.hpp"
#include "../Player.hpp"

#include <stack>

using namespace std;

typedef pair<int, int> Box;
typedef vector<Box> Chain;

class AlgorithmicPlayer: public Player {
    public:
    AlgorithmicPlayer(int id): Player(id) {};
    int get_move(Game &game); 
    string get_name() { return "Algorithmic"; }

    private:
    tuple<vector<Chain>, vector<Chain>, vector<Chain>> get_chains(Game &game) const;
}; 

tuple<vector<Chain>, vector<Chain>, vector<Chain>> AlgorithmicPlayer::get_chains(Game &game) const {
    vector<Chain> not_in_chain;
    vector<Chain> open;
    vector<Chain> half_open;

    stack<Box> dfs;
    bool *visited = new bool[game._width * game._height];
    for (int i = 0; i < game._height; i++) for (int j = 0; j < game._width; j++) visited[i*game._height+j] = false;

    for (int i = 0; i < game._height; i++) {
        for (int j = 0; j < game._width; j++) {
            dfs.push(make_pair(j, i));
            
            Chain c; 
            bool open_chain = false;
            while (!dfs.empty()) {
                Box b = dfs.top(); 
                dfs.pop(); 
                int x = b.first, y = b.second;
                int num_surrounding = game.num_surrounding_lines(x, y);

                if (x < 0 || x > game._width-1 || y < 0 || y > game._height-1) continue;

                if (visited[y*game._height+x]) continue;
                visited[y*game._height+x] = true;

                if (num_surrounding <= 1) {
                    Chain new_chain;
                    new_chain.push_back(make_pair(x, y));
                    not_in_chain.push_back(new_chain);
                }
                if (num_surrounding != 2 && num_surrounding != 3) continue;

                c.push_back(b);

                open_chain = num_surrounding == 3 || open_chain;

                if (!game._game_image[y][x][0]) dfs.push(make_pair(x, y-1));
                if (!game._game_image[y][x][1]) dfs.push(make_pair(x+1, y));
                if (!game._game_image[y][x][2]) dfs.push(make_pair(x, y+1));
                if (!game._game_image[y][x][3]) dfs.push(make_pair(x-1, y));
            }

            if (!c.empty()) {
                if (open_chain) open.push_back(c);
                else half_open.push_back(c);
            }
        }
    }

    delete[] visited;

    return make_tuple(not_in_chain, open, half_open); 
}

int AlgorithmicPlayer::get_move(Game &game) {
    game.print();
    int move = 0;

    auto chains = get_chains(game);
    vector<Chain> not_in_chain = get<0>(chains);
    vector<Chain> open_chains = get<1>(chains);
    vector<Chain> half_open_chains = get<2>(chains);

    if (not_in_chain.empty()) { 

    } else { 
        if (open_chains.empty()) { 

        } else {
            Chain longest_chain = open_chains.front();
            for (Chain c : open_chains) {
                if (c.size() > longest_chain.size()) longest_chain = c;
            }

            Box open_box;
            for (Box b : longest_chain) {
                if (game.num_surrounding_lines(b.first, b.second) == 3) {
                    open_box = b;
                    break;
                }
            }

            int row = open_box.second;
            int col = open_box.first;
            int direction = 0;
            for (; direction < 4; direction++) {
                if (!game._game_image[row][col][direction]) break;
            }

            cout << "Moving in " << row << ", " << col << ", " << direction << endl;

            move = game.get_move_from_rcd(row, col, direction);
        }
    }
    
    return move == -1 ? 0 : move;
}

#endif