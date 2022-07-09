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

                if (x < 0 || x > game._width-1 || y < 0 || y > game._height-1) continue;

                if (visited[y*game._height+x]) continue;
                visited[y*game._height+x] = true;

                int num_surrounding = game.num_surrounding_lines(x, y);
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
        if (open_chains.empty()) {
            Chain smallest_half_open = half_open_chains.front();
            for (Chain c : half_open_chains) {
                if (c.size() < smallest_half_open.size()) smallest_half_open = c;
            }

            Box half_open_box = smallest_half_open.front();
            int row = half_open_box.second;
            int col = half_open_box.first;
            int direction = 0;
            for (; direction < 4; direction++) {
                if (!game._game_image[row][col][direction]) break;
            }

            cout << "NO UNCHAINED; NO OPEN CHAINS: Moving in " << row << ", " << col << ", " << direction << endl;
            move = game.get_move_from_rcd(row, col, direction);
        } else {

        }
    } else { 
        if (open_chains.empty()) { 
            for (Chain unchained : not_in_chain) {
                bool found_move = false;
                
                Box unchained_box = unchained.front();
                int row = unchained_box.second;
                int col = unchained_box.first;
                int direction = 0; 

                for (; direction < 4 && !found_move; direction++) {
                    if (game._game_image[row][col][direction]) continue; 

                    auto other = game.get_other(row, col, direction);
                    int other_row = get<0>(other);
                    int other_col = get<1>(other);
                    int other_direction = get<2>(other);

                    if (game.get_move_from_rcd(other_row, other_col, other_direction) == -1) continue;

                    bool found = false;
                    for (Chain half_open_chain : half_open_chains) {
                        for (Box half_open_box : half_open_chain) {
                            if (half_open_box.first == other_col && half_open_box.second == other_row) found = true;
                        }
                    }
                    if (found) continue;

                    move = game.get_move_from_rcd(row, col, direction);
                    cout << "SOME UNCHAINED; NO OPEN CHAINS: Moving in " << row << ", " << col << ", " << direction << endl;
                    found_move = true;
                }

                if (found_move) break;
            }
        } else {
            Chain open_chain = open_chains.front();
            Box open_box;
            for (Box b : open_chain) {
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

            cout << "SOME UNCHAINED; OPEN CHAIN: Moving in " << row << ", " << col << ", " << direction << endl;

            move = game.get_move_from_rcd(row, col, direction);
        }
    }
    
    return move == -1 ? 0 : move;
}

#endif