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
    int take_half_open_chain(Chain &half_open, Game &game);
    int take_smallest_half_open(vector<Chain> &half_open_chains, Game &game);
    int take_open_chain(Chain &open, Game &game);
    int take_smallest_open(vector<Chain> &open_chains, Game &game);
    int take_unchained(vector<Chain> &unchained, vector<Chain> &half_open_chains, Game &game); 
    int double_cross(Chain &open_chain, Game &game);
    Chain get_smallest_chain(vector<Chain> &chains) const;
}; 

tuple<vector<Chain>, vector<Chain>, vector<Chain>> AlgorithmicPlayer::get_chains(Game &game) const {
    vector<Chain> unchained;
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
                    unchained.push_back(new_chain);
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

    return make_tuple(unchained, open, half_open); 
}

Chain AlgorithmicPlayer::get_smallest_chain(vector<Chain> &chains) const {
    Chain smallest_chain = chains.front();
    for (Chain c : chains) {
        if (c.size() < smallest_chain.size()) smallest_chain = c;
    }
    return smallest_chain;
}

int AlgorithmicPlayer::take_half_open_chain(Chain &half_open, Game &game) {
    Box half_open_box = half_open.front();
    int row = half_open_box.second;
    int col = half_open_box.first;
    int direction = 0;
    for (; direction < 4; direction++) {
        if (!game._game_image[row][col][direction]) break;
    }

    return game.get_move_from_rcd(row, col, direction);
}

int AlgorithmicPlayer::take_smallest_half_open(vector<Chain> &half_open_chains, Game &game) {
    Chain smallest_half_open = get_smallest_chain(half_open_chains);
    return take_half_open_chain(smallest_half_open, game);
}

int AlgorithmicPlayer::take_open_chain(Chain &open_chain, Game &game) {
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

    return game.get_move_from_rcd(row, col, direction);
}

int AlgorithmicPlayer::take_smallest_open(vector<Chain> &open_chains, Game &game) {
    Chain smallest_open = get_smallest_chain(open_chains);
    return take_open_chain(smallest_open, game);
}

int AlgorithmicPlayer::double_cross(Chain &open_chain, Game &game) {
    Box half_open_box = open_chain.front();
    Box open_box = open_chain.back();
    for (Box b : open_chain) {
        if (game.num_surrounding_lines(b.first, b.second) != 3) half_open_box = b;
        else open_box = b;
    }

    int row = half_open_box.second;
    int col = half_open_box.first;
    int direction = 0;
    for (; direction < 4; direction++) {
        if (!game._game_image[row][col][direction]) {
            auto other = game.get_other(row, col, direction);
            int other_row = get<0>(other);
            int other_col = get<1>(other);
            int other_direction = get<2>(other);
            if (other_row == open_box.second && other_col == open_box.first) continue;
            break;
        }
    }

    if (game.get_move_from_rcd(row, col, direction) == -1) {
        for (direction = 0; direction < 4; direction++) {
            if (!game._game_image[row][col][direction]) break;
        }
    }

    return game.get_move_from_rcd(row, col, direction);
}

int AlgorithmicPlayer::take_unchained(vector<Chain> &unchained, vector<Chain> &half_open_chains, Game &game) {
    for (Chain unchained : unchained) {
        Box unchained_box = unchained.front();
        int row = unchained_box.second;
        int col = unchained_box.first;
        int direction = 0; 

        for (; direction < 4; direction++) {
            if (game._game_image[row][col][direction]) continue; 

            auto other = game.get_other(row, col, direction);
            int other_row = get<0>(other);
            int other_col = get<1>(other);
            int other_direction = get<2>(other);

            bool found = false;
            for (Chain half_open_chain : half_open_chains) {
                for (Box half_open_box : half_open_chain) {
                    if (half_open_box.first == other_col && half_open_box.second == other_row) found = true;
                }
            }
            if (found) continue;

            return game.get_move_from_rcd(row, col, direction);
        }
    }

    return 0;
}

int AlgorithmicPlayer::get_move(Game &game) {
    auto chains = get_chains(game);
    vector<Chain> unchained = get<0>(chains);
    vector<Chain> open_chains = get<1>(chains);
    vector<Chain> half_open_chains = get<2>(chains);

    if (unchained.empty()) { 
        if (open_chains.empty()) {
            return take_smallest_half_open(half_open_chains, game);
        } else {
            if (half_open_chains.empty()) {
                return take_open_chain(open_chains.front(), game);
            } else {
                if (open_chains.size() == 1) {
                    if (open_chains.front().size() == 2) {
                        Chain smallest_half_open = get_smallest_chain(half_open_chains);

                        if (smallest_half_open.size() <= 2) {
                            return take_open_chain(open_chains.front(), game);
                        } else {
                            return double_cross(open_chains.front(), game);
                        }
                    } else {
                        return take_open_chain(open_chains.front(), game);
                    }
                } else {                  
                    return take_smallest_open(open_chains, game);    
                }
            }
        }
    } else { 
        if (open_chains.empty()) {
            return take_unchained(unchained, half_open_chains, game); 
        } else {
            return take_open_chain(open_chains.front(), game);
        }
    }

    return 0;
}

#endif