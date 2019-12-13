#include "neural_network.h"
#include <iostream>

#define FILE "PICTURE_CONVERTER_FILE.txt"
#define COUNT 275000

Matrix getAnswer(int n)
{
    std::vector<float> vec;
    for(int i = 0; i < 10; i++)
    {
        
        vec.push_back(-1);
        
    }

    vec[n] = 1;

    return Matrix(vec);
}

int main(int argc, char** args)
{   
    const std::string base_filepath = "data_set/trainingSet/trainingSet/";
    std::ifstream file;
    auto nn = neuralNetwork({784,16,12,10},tan_h);

    nn.set_learning_rate(0.0008);

    for(int i = 0; i < COUNT; i++)
    {
        std::vector<float> input;


        int random_number = rand() % 10;
        std::string filepath = base_filepath + std::to_string(random_number) + "/";
        filepath = "python3 picture-getter.py -R " + filepath;

        std::cout<<i<<" out of "<<COUNT<<" samples done";

        system(filepath.c_str());


        file.open(FILE);

        for(int p = 0; p < 784; p++)
        {
            float t;
            file>>t;

            input.push_back(t);
        }

        file.close();

        Matrix input_matrix(input);
        Matrix answer = getAnswer(random_number);


        nn.train_supervised(input_matrix,answer);

    }

    nn.save_network("mnist_neural_network"); 

    neuralNetwork mm;

    mm.import_network("mnist_neural_network.nn");

    while(true)
    {
        std::string filepath;
        std::vector<float> input;
        std::cin>>filepath;

        try
        {
            filepath = "python3 picture-getter.py "+filepath;
            system(filepath.c_str());

            
            file.open(FILE);

            for(int i = 0; i < 784; i++)
            {
                float t;
                file>>t;

                input.push_back(t);
            }

            file.close();

            mm.feedForward(Matrix(input)).print();
            
        }
        catch(const std::exception& e)
        {
            std::cout<<"\nsomething went wrong";
            continue;
        }
        
    }

    return 0;
}