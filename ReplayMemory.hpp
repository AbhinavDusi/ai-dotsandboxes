#ifndef REPLAY_MEMORY_H
#define REPLAY_MEMORY_H

#include <vector>
#include <random>
#include <ctime>

using namespace std;

typedef struct Experience {
    vector<double> state_0;
    int action; 
    double reward;
    vector<double> state_1;
    bool terminal;
    Experience(vector<double> state_0, int action, double reward, vector<double> state_1, bool terminal): 
        state_0(state_0), action(action), reward(reward), state_1(state_1), terminal(terminal) {};
} Experience;

class ReplayMemory {
    public:
    vector<Experience> _memory;
    int _capacity;
    int _push_count;
    ReplayMemory(int capacity): _capacity(capacity) {};
    void add_experience(Experience e);
    bool can_provide_sample(int minibatch_size) { return _memory.size() >= minibatch_size; }; 
    vector<Experience> get_sample(int minibatch_size) const;
    static mt19937 rng;
};

mt19937 ReplayMemory::rng(time(nullptr));

void ReplayMemory::add_experience(Experience e) {
    if (_memory.size() < _capacity) _memory.push_back(e); 
    else _memory[_push_count%_capacity] = e;
    _push_count++;
}

vector<Experience> ReplayMemory::get_sample(int minibatch_size) const {
    vector<Experience> sample;
    for (int i = 0; i < minibatch_size; i++) {
        Experience experience = _memory[rng()%_memory.size()];
        sample.push_back(experience);
    }
    return sample;
}

#endif