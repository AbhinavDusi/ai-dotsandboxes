#include <iostream>
#include <vector>

#include "NeuralNet.hpp"

int main() {
    vector<int> topology; 
    topology.push_back(2);
    topology.push_back(2);
    topology.push_back(2);

    double alpha = 0.5;
    double eta = 0.15;

    NeuralNet net1(topology, alpha, eta);
    NeuralNet net2(topology, alpha, eta); 

    
}