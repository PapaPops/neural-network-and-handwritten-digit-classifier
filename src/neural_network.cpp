#include "neural_network.h"



Matrix map(Matrix inputs, float(*func)(float))
{
    for(int i = 0; i < inputs.getRows(); i++)
    {
        for(int j = 0; j < inputs.getCols(); j++)
        {
            inputs.set(i,j,func(inputs.get(i,j)));
        }
    }

    return inputs;
}

Matrix activate(activationFunction func, Matrix& inputs)
{
    if(func == sigmoid)
       return map(inputs,Function::sigmoid);
    else if(func == arctan)
        return map(inputs,Function::arctan);
    else if(func == tan_h)
        return map(inputs,Function::tanh);
    else
        return map(inputs, Function::relu);

}

Matrix activation_derivative(activationFunction func, Matrix& input)
{
    if(func == sigmoid)
        return map(input,Function::sigmoid_d);
    else if(func == arctan)
        return map(input,Function::arctan_d);
    else if(func == tan_h)
        return map(input,Function::tanh_d);
    else
        return map(input,Function::relu_d);
}


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
        inputs = layers[i].multiply(inputs).add(biases[i]);
        
        inputs = activate(this->activation,inputs);
    }

    return inputs;
}



Matrix neuralNetwork::train_supervised(Matrix inputs, Matrix target_results)
{
    if(inputs.getRows() != structure[0] || inputs.getCols() != 1 ||
         target_results.getRows() != structure[structure.size()-1] || target_results.getCols() != 1)
            throw std::invalid_argument("inputs or target matrix are in the wrong dimensions");

    

    //feedforward algorithm
    Matrix outputs = inputs;
    std::vector<Matrix> layer_inputs; 
    layer_inputs.push_back(inputs);
    for(int i = 0; i < layers.size() ; i++)
    {
        outputs = layers[i].multiply(outputs).add(biases[i]);

        outputs = activate(this->activation,outputs);

        layer_inputs.push_back(outputs);
    } 
    // see feedforward


    //BACKPROPAGATION
    //getting the errors
    std::vector<Matrix> errors;

    //generation of the empty error matrices
    for(int i = 1; i < structure.size(); i++)
    {
        errors.push_back(Matrix(structure[i],1,0));
    }
    //getting the final error
    errors[errors.size()-1] = target_results.subtract(outputs);

    std::cout<<"cost:\n";

    errors[errors.size()-1].print();

    std::cout<<"\n\n";

    //propagating back the errors for each hidden layer
    for(int i = layers.size() - 1; i >= 1; i--)
    {
        errors[i-1] = layers[i].transpose().multiply(errors[i]);
    }

    //calculating the gradient and adding the difference to the individual layers
    for(int i = layers.size() - 1; i>=0; i--)
    {
        auto gradient = activation_derivative(this->activation,layer_inputs[i+1])
            .hadamardProduct(errors[i]).multiply(this->LEARNING_RATE);

        auto output_transposed = layer_inputs[i].transpose();
        
        auto delta_weights = gradient.multiply(output_transposed);

        layers[i]  =  layers[i].add(delta_weights);
        biases[i] = biases[i].add(gradient);
    }


    return outputs;
}



void neuralNetwork::save_network(std::string& file_path)
{
    //saving neural network in a file
}


void neuralNetwork::import_network(std::string& file_path)
{
    //importing the weights and biases and shape of the neural network from that file
}



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

void neuralNetwork::set_learning_rate(float learning_rate) //it would be advised not to tinker with this
{
    this->LEARNING_RATE = learning_rate;
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


