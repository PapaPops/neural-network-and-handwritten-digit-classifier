
#include "functions.h"

const float E = 2.71828;


float Function::sigmoid(float nr)
{
    return 1/(1+pow(E,-nr));
}

float Function::tanh(float nr)
{
    return (pow(E,nr) - pow(E,-nr))/
                (pow(E,nr) + pow(E,-nr));
}

float Function::relu(float nr)
{
    return (nr <= 0)? 0 : nr;
}

float Function::arctan(float nr)
{
    return atan(nr);
}

//derivatives

float Function::sigmoid_d(float nr)
{
    float result = nr;

     return result*(1-result);
}
float Function::tanh_d(float nr)
{
    return 1-pow(nr,2);
}
float Function::relu_d(float nr)
{
    return (nr<=0)? 0 : 1;
}
float Function::arctan_d(float nr)
{
    return 1 / (pow(nr,2) + 1);
}


//helper functions

