#include "neural_network.h"
#include <iostream>

int main(int argc, char** args)
{   
    //calculating xor;
    std::vector<Matrix> options;
    std::vector<Matrix> answers;
    for(int i = 0; i < 4; i++)
    {
        options.push_back(Matrix(2,1,0));
        answers.push_back(Matrix(1,1,0));
    }

    options[0].set(0,0,1);options[0].set(1,0,1);
    options[1].set(0,0,-1);options[1].set(1,0,1);
    options[2].set(0,0,1);options[2].set(1,0,-1);
    options[3].set(0,0,-1);options[3].set(1,0,-1);

    answers[0].set(0,0,0);
    answers[1].set(0,0,1);
    answers[2].set(0,0,1);
    answers[3].set(0,0,0);


    


    auto nn = neuralNetwork({2,3,3,1},tan_h);

    for(int i = 0; i < 25000;i++)
    {
        int nr = rand() % 4;
        nn.train_supervised(options[nr],answers[nr]);
    }

    nn.save_network("neural_network");

    neuralNetwork mm;

    mm.import_network("./neural_network.nn");

    while(true)
    {
       auto a = Matrix(2,1,0);
       float first,second;
       std::cin>>first>>second;

       a.set(0,0,first);a.set(1,0,second);
       mm.feedForward(a).print();
    }

    return 0;
}