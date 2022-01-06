#include <iostream>

#include "NeuralNet.hpp"

using namespace std;

void exp_decay(double *x, double x_0, double decay, int n) {
    *x = x_0*exp(-1*decay*n);
}

int main() {
    vector<int> topology;
    topology.push_back(2);
    topology.push_back(4);
    topology.push_back(1);

    double alpha = 0.5;
    double eta = 0.15;

    int alpha_decay = 0.0001;
    int eta_decay = 0.0001; 

    NeuralNet net(topology, alpha, eta);
    mt19937 rng;

    int T = 2000;
    for (int i = 0; i < T; i++) {
        int a = rng()%2;
        int b = rng()%2;

        vector<double> input; 
        input.push_back(a);
        input.push_back(b);
        net.feed_forward(input);

        vector<double> target;
        target.push_back(a^b);
        net.back_prop(target);

        exp_decay(&(net._alpha), alpha, alpha_decay, i);
        exp_decay(&(net._eta), eta, eta_decay, i);
    }

    vector<double> input;
    input.push_back(1);
    input.push_back(1);

    net.feed_forward(input);

    vector<double> result = net.get_result();

    cout << result.front() << endl;

    return 0;
}   