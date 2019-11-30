#include "matrix.h"
#include "functions.h"
#include <fstream>

enum activationFunction{
    sigmoid,tan_h,arctan,relu
};
class neuralNetwork
{
    public:
        neuralNetwork(std::vector<int>,activationFunction);
        neuralNetwork(){}

        Matrix feedForward(Matrix);
        Matrix train_supervised(Matrix,Matrix); //supervised learning 


        void save_network(const std::string&);
        void import_network(const std::string&);


        void print_layer(int);
        void print_network();
        void print_structure();
        void print_biases();

        void set_learning_rate(float);
        
        Matrix* getLayer(int);


    private:

        activationFunction activation;
        std::vector<Matrix> layers; //weight matrices 
        std::vector<Matrix> biases;
        std::vector<int> structure;
        float LEARNING_RATE = 0.02;
};