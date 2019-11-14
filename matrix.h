#pragma once
#include <vector>
#include <iostream>

class Matrix
{
    public:
        Matrix(Matrix&);
        Matrix(int,int,float);
        ~Matrix();


        float get(int, int);
        void set(int,int,float);

        Matrix add(Matrix&);
        Matrix subtract(Matrix&);

        Matrix multiply(Matrix&); 
        Matrix multiply(float); // scalar

        Matrix divide(float); //scalar

        Matrix transpose();

        void print();

        int getCols();
        int getRows();


    private:
        int m_cols, m_rows;
        std::vector<std::vector<float>> matrix;
    
};
