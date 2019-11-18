#include "functions.h"

float power(float,int);


float Function::sigmoid(float nr)
{
    return nr;
}

float Function::tanh(float nr)
{
    return nr;
}

float Function::rrelu(float nr)
{
    return nr;
}

float Function::arctan(float nr)
{
    return nr;
}

//derivatives

float Function::sigmoid_d(float nr)
{
    return nr;
}
float Function::tanh_d(float nr)
{
    return nr;
}
float Function::rrelu_d(float nr)
{
    return nr;
}
float Function::arctan_d(float nr)
{
    return nr;
}


//helper functions

float power(float nr,int toPower)
{
    if(power == 0)
        return 1;
    if(power < 0)
    {
        return 1/power(nr,-toPower);
    }
    else
    {
        float result = nr;

        for(int i = 0;i<toPower-1;i++)
        {
            result*=nr;
        }

        return result;
    }
    
}