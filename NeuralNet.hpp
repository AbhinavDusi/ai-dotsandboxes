#ifndef NEURAL_NET_H
#define NEURAL_NET_H

#include <vector>
#include <random>

typedef struct Connection {
    double weight;
    double delta; 
} Connection; 

class Neuron; 

typedef std::vector<Neuron> Layer; 

class Neuron {
    public:
    Neuron(int num_outputs);
    static double activation_function(double x) { return tanh(x); }
    static double activation_function_derivative(double y) { return 1.0-y*y; }
    void calc_output_error(double target); 
    void calc_hidden_error(const Layer& next_layer);
    void nudge_output_weights(const Layer& next_layer);
    std::vector<Connection> _output_weights; 
    double _val; 
    double _error; 

    private:
    static double random() { return Neuron::rng()/(double) Neuron::rng.max(); }
    static std::mt19937 rng; 
    static double alpha; 
    static double eta; 
}; 

std::mt19937 Neuron::rng(time(nullptr));
double Neuron::alpha = 0.5; 
double Neuron::eta = 0.15; 

Neuron::Neuron(int num_outputs) {
    for (int i = 0; i < num_outputs; i++) {
        _output_weights.push_back(Connection());
        _output_weights.back().weight = Neuron::random();
    }
}

void Neuron::calc_output_error(double target) {
    _error = target-_val;
}

void Neuron::calc_hidden_error(const Layer& next_layer) {
    double error = 0.0; 
    for (int i = 0; i < next_layer.size()-1; i++) {
        error += _output_weights[i].weight*next_layer[i]._error;
    }
    _error = error;
}

void Neuron::nudge_output_weights(const Layer& next_layer) {
    for (int i = 0; i < next_layer.size()-1; i++) {
        double old_delta = _output_weights[i].delta; 
        double new_delta = Neuron::eta*next_layer[i]._error*activation_function_derivative(next_layer[i]._val)*_val
            +Neuron::alpha*old_delta; 

        _output_weights[i].delta = new_delta; 
        _output_weights[i].weight += new_delta; 
    }
}

class NeuralNet {
    public:
    NeuralNet(const std::vector<int>& topology); 
    void feed_forward(const std::vector<double>& input); 
    void back_prop(const std::vector<double>& target);
    std::vector<double> get_result() const;

    private:
    std::vector<Layer> _layers; 
};

NeuralNet::NeuralNet(const std::vector<int>& topology) {
    for (int i = 0; i < topology.size(); i++) {
        _layers.push_back(Layer());
        int num_outputs = i < topology.size()-1 ? topology[i+1] : 0;

        for (int j = 0; j < topology[i]+1; j++) {
            _layers.back().push_back(Neuron(num_outputs));
        }

        _layers.back().back()._val = 1.0;
    }
}

void NeuralNet::feed_forward(const std::vector<double>& input) {
    for (int i = 0; i < input.size(); i++) {
        _layers[0][i]._val = input[i];
    }

    for (int i = 0; i < _layers.size()-1; i++) {
        for (int j = 0; j < _layers[i+1].size()-1; j++) {
            double weighted_sum = 0.0; 
            for (int k = 0; k < _layers[i].size(); k++) {
                weighted_sum += _layers[i][k]._val*_layers[i][k]._output_weights[j].weight;
            }
            _layers[i+1][j]._val = Neuron::activation_function(weighted_sum); 
        }
    }
}

void NeuralNet::back_prop(const std::vector<double>& target) {
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
            _layers[i][j].nudge_output_weights(_layers[i+1]); 
        }
    }
}

std::vector<double> NeuralNet::get_result() const {
    std::vector<double> result; 
    for (int i = 0; i < _layers.back().size()-1; i++) {
        result.push_back(_layers.back()[i]._val); 
    }
    return result; 
}

#endif 