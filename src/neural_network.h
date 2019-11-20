#include "matrix.h"
#include "functions.h"

enum activationFunction{
    sigmoid,tan_h,arctan,relu
};
class neuralNetwork
{
    public:
        neuralNetwork(std::vector<int>,activationFunction);
        Matrix feedForward(Matrix);


        void save_network();
        void import_network();


        void print_layer(int);
        void print_network();
        void print_structure();
        void print_biases();
        
        Matrix* getLayer(int);


    private:
        activationFunction activation;
        std::vector<Matrix> layers; //weight matrices 
        std::vector<Matrix> biases;
        std::vector<int> structure;
};