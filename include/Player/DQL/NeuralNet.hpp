#ifndef NEURAL_NET_H
#define NEURAL_NET_H

#include <vector>
#include <random>
#include <ctime>

using namespace std;

class Neuron; 

typedef vector<Neuron> Layer; 

class Neuron {
    public:
    Neuron(int num_outputs);
    static double relu_activation(double x) { return x > 0 ? x : 0; }
    static double relu_activation_derivative(double y) { return y>0; }
    void calc_output_error(double target); 
    void calc_hidden_error(const Layer& next_layer);
    void nudge_output_weights(const Layer& next_layer, double alpha);
    vector<double> _output_weights; 
    double _val; 
    double _error; 

    private:
    static double random() { return Neuron::rng()/(double) Neuron::rng.max(); }
    static mt19937 rng; 
}; 

mt19937 Neuron::rng(time(nullptr));

Neuron::Neuron(int num_outputs) {
    for (int i = 0; i < num_outputs; i++) {
        _output_weights.push_back(Neuron::random());
    }
}

void Neuron::calc_output_error(double target) {
    _error = target-_val;
}

void Neuron::calc_hidden_error(const Layer& next_layer) {
    double error = 0.0; 
    for (int i = 0; i < next_layer.size()-1; i++) {
        error += _output_weights[i]*next_layer[i]._error;
    }
    _error = error;
}

void Neuron::nudge_output_weights(const Layer& next_layer, double alpha) {
    for (int i = 0; i < next_layer.size()-1; i++) {
        double delta = alpha*next_layer[i]._error*relu_activation_derivative(next_layer[i]._val)*_val;
        _output_weights[i] += delta; 
    }
}

class NeuralNet {
    public:
    NeuralNet(const vector<int>& topology, double alpha); 
    NeuralNet() {};
    void feed_forward(const vector<double>& input); 
    void back_prop(const vector<double>& target);
    vector<double> get_result() const;
    void load(NeuralNet &net);
    double _alpha; 

    private:
    vector<Layer> _layers; 
};

NeuralNet::NeuralNet(const vector<int>& topology, double alpha): _alpha(alpha) {
    for (int i = 0; i < topology.size(); i++) {
        _layers.push_back(Layer());
        int num_outputs = i < topology.size()-1 ? topology[i+1] : 0;

        for (int j = 0; j < topology[i]+1; j++) {
            _layers.back().push_back(Neuron(num_outputs));
        }

        _layers.back().back()._val = 1.0;
    }
}

void NeuralNet::feed_forward(const vector<double>& input) {
    for (int i = 0; i < input.size(); i++) {
        _layers[0][i]._val = input[i];
    }

    for (int i = 0; i < _layers.size()-1; i++) {
        for (int j = 0; j < _layers[i+1].size()-1; j++) {
            double weighted_sum = 0.0; 
            for (int k = 0; k < _layers[i].size(); k++) {
                weighted_sum += _layers[i][k]._val*_layers[i][k]._output_weights[j];
            }
            
            _layers[i+1][j]._val = Neuron::relu_activation(weighted_sum);
        }
    }
}

void NeuralNet::back_prop(const vector<double>& target) {
    for (int i = 0; i < _layers.back().size()-1; i++) {
        _layers.back()[i].calc_output_error(target[i]);
    }

    for (int i = _layers.size()-2; i >= 0; i--) {
        for (int j = 0; j < _layers[i].size()-1; j++) {
            _layers[i][j].calc_hidden_error(_layers[i+1]);
        }
    }

    for (int i = 0; i < _layers.size()-1; i++) {
        for (int j = 0; j < _layers[i].size(); j++) {
            _layers[i][j].nudge_output_weights(_layers[i+1], _alpha); 
        }
    }
}

vector<double> NeuralNet::get_result() const {
    vector<double> result; 
    for (int i = 0; i < _layers.back().size()-1; i++) {
        result.push_back(_layers.back()[i]._val); 
    }
    return result; 
}

void NeuralNet::load(NeuralNet &net) {
    _layers = net._layers;
    _alpha = net._alpha;
}

#endif 
