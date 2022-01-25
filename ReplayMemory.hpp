#ifndef REPLAY_MEMORY_H
#define REPLAY_MEMORY_H

typedef struct Experience {
    vector<double> state_0;
    int action; 
    double reward;
    vector<double> state_1;
    Experience(vector<double> state_0, int action, double reward, vector<double> state_1): 
        state_0(state_0), action(action), reward(reward), state_1(state_1) {};
} Experience;

class ReplayMemory {
    public:
    vector<Experience> _memory;
    int _capacity;
    int _push_count;
    ReplayMemory(int capacity): _capacity(capacity) {};
    void add_experience(Experience e);
    bool can_provide_sample(int minibatch_size) { return rm._memory.size() >= minibatch_size; }; 
};

void ReplayMemory::add_experience(Experience e) {
    if (_memory.size() < _capacity) _memory.push_back(e); 
    else _memory[_push_count%_capacity] = e;
    _push_count++;
}

#endif