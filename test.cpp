#include <vector>
#include <random>
#include <iostream>

#include "NeuralNet.hpp"

void exp_decay(double *x, double x_0, double decay, int n) {
    *x = x_0*exp(-1*decay*n);
}    

int main() {
    std::vector<int> topology; 
    topology.push_back(2); 
    topology.push_back(4); 
    topology.push_back(1);     
    
    double alpha_0 = 0.5;
    double alpha_decay = 0.001;

    double eta_0 = 0.15;
    double eta_decay = 0.001; 

    NeuralNet net(topology, alpha_0, eta_0); 

    std::mt19937 rng(time(nullptr));

    for (int i = 0; i < 2000; i++) {
        exp_decay(&(net._alpha), alpha_0, alpha_decay, i);
        exp_decay(&(net._eta), eta_0, eta_decay, i);

        int a = rng()%2; 
        int b = rng()%2;

        std::vector<double> input; 
        input.push_back(a); 
        input.push_back(b); 

        std::vector<double> target; 
        target.push_back(a^b); 

        net.feed_forward(input);
        net.back_prop(target); 
    }

    int a = rng()%2;
    int b = rng()%2;

    std::vector<double> input; 
    input.push_back(a); 
    input.push_back(b); 

    net.feed_forward(input);

    std::vector<double> result = net.get_result(); 

    std::cout << a << " XOR " << b << " = " << result.front() << std::endl; 

    return 0; 
}