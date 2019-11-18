#include "neural_network.h"
#include "functions.h"

neuralNetwork::neuralNetwork(std::vector<int> structure,activationFunction function)
{
    srand(time(NULL));


    this->activation = function;

    if(structure.size() < 3)
        throw std::invalid_argument("the structure vector must have at least three elements");
    
    for(int i : structure)
    {
        if(i<=0)
            throw std::invalid_argument("a layer size cannot be smaller than 1");
    }

    this->structure = structure;
    
    for(int i = 0; i < this->structure.size()-1; i++)
    {
        auto layer = Matrix(structure[i+1],structure[i],0);
        auto bias = Matrix(structure[i+1],1,0);


        this->layers.push_back(layer);
        this->biases.push_back(bias);

       this->layers[i].randomize(); this->biases[i].randomize();
    }

    

}
//feed forward algorithm matrix multiplication without the training
Matrix neuralNetwork::feedForward(Matrix inputs)
{
    if(inputs.getRows() != structure[0] || inputs.getCols() != 1)
    {
        throw std::invalid_argument("input is in wrong matrix dimensions");
    }

    
    for(int i = 0; i < layers.size() ; i++)
    {
        //inputs.print(); std::cout<<"\n\n";
        inputs = layers[i].multiply(inputs).add(biases[i]);
        
    }

    return inputs;
}


//printing neural network information 



void neuralNetwork::print_network()
{
    for(auto& i : this->layers)
    {
        i.print();
        std::cout<<"\n";
    }  
}

void neuralNetwork::print_layer(int index)
{
    this->layers[index].print();
    std::cout<<"\n";
}

void neuralNetwork::print_biases()
{
    for(auto& i : this->biases)
    {
        i.print();
        std::cout<<"\n";
    }
}

void neuralNetwork::print_structure()
{
    std::cout<<"input layer: "<<structure[0]<<"\n";
    std::cout<<"hidden layers: ";
    for(int i = 1; i < structure.size()-1; i++)
    {
        std::cout<<structure[i]<<" ";
    } std::cout<<"\n";
    std::cout<<"output layer: "<<structure[structure.size()-1]<<"\n";
}


//getLayer

Matrix* neuralNetwork::getLayer(int index)
{
    if(index >= this->layers.size())
    {
        throw std::invalid_argument("index outside of bounds");
    }

    else return &layers[index];
}


