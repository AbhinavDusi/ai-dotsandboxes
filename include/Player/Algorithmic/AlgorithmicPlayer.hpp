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
    int num_surrounding_lines(Game &game, int x, int y) const;
    tuple<vector<Chain>, vector<Chain>, vector<Chain>> get_chains(Game &game) const;
}; 

int AlgorithmicPlayer::num_surrounding_lines(Game &game, int x, int y) const {
    GameImage game_image = game._game_image;
    return game_image[y][x][0]+game_image[y][x][1]+game_image[y][x][2]+game_image[y][x][3];
}

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
                int num_surrounding = num_surrounding_lines(game, x, y);

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

    vector<Move> moves = game._moves;

    auto chains = get_chains(game);
    vector<Chain> not_in_chain = get<0>(chains);
    vector<Chain> open_chains = get<1>(chains);
    vector<Chain> half_open_chains = get<2>(chains);

    if (not_in_chain.empty()) { // All boxes are in chains

    } else { // Some boxes are not in chains
        if (open_chains.empty()) { // Open chains available

        } else { // No open chains

        }
    }
    
    return 0;
}

#endif