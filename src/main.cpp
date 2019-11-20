#include "neural_network.h"
#include <iostream>



int main(int argc, char** args)
{   

    auto nn = neuralNetwork({2,2,2},tan_h);

    auto matrix = Matrix(2,1,0);

    matrix.randomize(); matrix.print(); std::cout<<"\n\n";
    
    nn.feedForward(matrix).print();
        


    return 0;
}