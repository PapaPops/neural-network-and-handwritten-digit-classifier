#include "neural_network.h"

activationFunction selectActivation(int);

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
        
        auto delta_weights = gradient.multiply(layer_inputs[i].transpose());

        layers[i]  =  layers[i].add(delta_weights);
        biases[i] = biases[i].add(gradient);
    }


    return outputs;
}



void neuralNetwork::save_network(const std::string& name)
{
    auto file_name = name + ".nn";

    std::ofstream neural_network_file;

    neural_network_file.open(file_name);

    if(!neural_network_file.is_open())
    {
        throw std::invalid_argument("something went wrong with the file\n");
    }

    for(auto& i : structure)
    {
        neural_network_file<<i<<" ";
    }

    neural_network_file<<"| ";

    neural_network_file<<activation<<" | ";

    for(int i = 0; i < layers.size(); i++)
    {
        for(int j = 0; j < layers[i].getRows(); j++)
        {
            for(int t = 0; t < layers[i].getCols(); t++)
            {
                neural_network_file<<layers[i].get(j,t)<<" ";
            }
        }
    }

    neural_network_file<<"| ";

    for(int i = 0; i < biases.size(); i++)
    {
        for(int j = 0; j < biases[i].getRows(); j++)
        {
            for(int t = 0; t < biases[i].getCols(); t++)
            {
                neural_network_file<<biases[i].get(j,t)<<" ";
            }
        }
    }

    neural_network_file<<"| "<<this->LEARNING_RATE;



    neural_network_file.close();
}


void neuralNetwork::import_network(const std::string& file_path)
{
    std::vector<Matrix> layers;
    std::vector<int> structure;
    std::vector<Matrix> biases;


    std::ifstream input_neural(file_path);

    if(!input_neural.is_open())
        throw std::invalid_argument("Could not open the input file\n");
    
    std::string input_char;
    std::vector<std::string> input_vec;

    while(input_neural>>input_char)
    {
        input_vec.push_back(input_char);
    }

    int count = 0;
    for(;input_vec[count]!="|";count++)
    {
        structure.push_back(std::stoi(input_vec[count]));
    }
    this->structure = structure; count++;

    for(int i = 0; i < this->structure.size()-1; i++)
    {
        auto layer = Matrix(structure[i+1],structure[i],0);
        auto bias = Matrix(structure[i+1],1,0);


        layers.push_back(layer);
        biases.push_back(bias);

    }

    //activation
    this->activation = selectActivation(std::stoi(input_vec[count])); count++; // I don't really like this in case I would've wanted to add more activation functions

    for(int i = 0; i < layers.size(); i++)
    {
        for(int j = 0; j < layers[i].getRows(); j++)
        {
            for(int t = 0; t < layers[i].getCols(); t++)
            {
                layers[i].set(j,t, std::stof(input_vec[++count]) );
            }
        }
    }

    count++;

    for(int i = 0; i < biases.size(); i++)
    {
        for(int j = 0; j < biases[i].getRows(); j++)
        {
            for(int t = 0; t < biases[i].getCols(); t++)
            {
                biases[i].set(j,t,std::stof(input_vec[++count]));
            }
        }
    }
    
    count += 2;

    this->LEARNING_RATE = std::stof(input_vec[count]);

    this->layers = layers;
    this->biases = biases;
    
    
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
        throw std::invalid_argument("index outside of bounds\n");
    }

    else return &layers[index];
}

activationFunction selectActivation(int nr)
{
    switch (nr)
    {
        case 0 : return sigmoid;
            break;
        case 1: return tan_h;
            break;
        case 2: return arctan;
            break;
        case 3: return relu;
            default:
            throw std::invalid_argument("no such activation function\n");
    }
}


