#include "functions.h"
#include <math.h>

const float E = 2.71828;


float Function::sigmoid(float nr)
{
    return 1/(1+power(E,-nr));
}

float Function::tanh(float nr)
{
    return (power(E,nr) - power(E,-nr))/
                (power(E,nr) + power(E,-nr));
}

float Function::relu(float nr)
{
    return (nr <= 0)? 0 : nr;
}

float Function::arctan(float nr)
{
    return (float)arctan(nr);
}

//derivatives

float Function::sigmoid_d(float nr)
{
    float result = sigmoid(nr);

    result/(1-result);
}
float Function::tanh_d(float nr)
{
    return 1-power(tanh(nr),2);
}
float Function::relu_d(float nr)
{
    return (nr<=0)? 0 : 1;
}
float Function::arctan_d(float nr)
{
    return 1 / (power(nr,2) + 1);
}


//helper functions

float power(float nr,int toPower)
{
    if(toPower == 0)
        return 1;

    else if(toPower > 0)
    {
        int product = 1;
        for(int i = 1; i <= toPower; i++)
        {
            product *= nr;
        }

        return product;
    }

    else
        return (float)1/power(nr,-toPower);
}
