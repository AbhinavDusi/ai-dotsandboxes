#ifndef REPLAY_MEMORY_H
#define REPLAY_MEMORY_H

typedef struct Experience {
    vector<double> state;
    int action; 
    double reward;
    vector<double> new_state;
    Experience(vector<double> state, int action, double reward, vector<double> new_state): 
        state(state), action(action), reward(reward), new_state(new_state) {};
} Experience;

class ReplayMemory {
    public:
    vector<Experience> _memory;
    int _capacity;
    ReplayMemory(int capacity): _capacity(capacity) {};
    void add_experience(Experience e) { if (_memory.size() < _capacity) _memory.push_back(e); }
};

#endif