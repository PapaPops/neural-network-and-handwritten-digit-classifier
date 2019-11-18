#pragma once
#include <vector>
#include <iostream>
#include <cstdlib>
#include <time.h>

class Matrix
{
    public:
        Matrix(const Matrix&);
        Matrix(int,int,float);


        float get(int, int) const;
        void set(int,int,float);

        Matrix add(Matrix&);
        Matrix subtract(Matrix&);

        Matrix multiply(Matrix&); 
        Matrix multiply(float); // scalar

        Matrix divide(float); //scalar

        Matrix transpose();


        void print() const;
        void randomize();
         


        int getCols() const;
        int getRows() const;


    private:
        int m_cols, m_rows;
        std::vector<std::vector<float>> matrix;
    
};
