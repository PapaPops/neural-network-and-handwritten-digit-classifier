#include "./matrix.h"


Matrix::~Matrix(){}

Matrix::Matrix(Matrix& m)
{
    std::vector<std::vector<float>> result;
    for (int i = 0; i < m.getRows(); i++)
        {
            std::vector<float> t;
            for(int j = 0; j < m.getCols(); j++)
            {
                t.push_back(m.get(i,j));
            }
            result.push_back(t);
        }
    
    matrix = result;
    this->m_cols = result.size();
    this->m_rows = result[0].size();

}


Matrix::Matrix(int rows, int cols , float element = 0) 
{
    if(cols <= 0 || rows <= 0)
    {
        throw std::invalid_argument("received negative value for either the cols or rows");
    }
    
    this->m_rows = rows; this->m_cols = cols;

    for(int i = 0; i < rows ; i++)
    {
        std::vector<float> t;
        for(int j = 0; j < cols; j++)
        {
            t.push_back(element);
        }
        matrix.push_back(t);
    }
}

//operations


Matrix Matrix::add(Matrix& m)
{
    if(this->getRows() != m.getRows() || this->getCols() != m.getCols())
        throw std::invalid_argument("the matrix that was passed as an argument doesn't have the same row anc col length as the matrix object");
    
    Matrix result(this->getRows(),this->getCols());

    for(int i = 0; i < this->getRows(); i++)
    {
        for(int j = 0; j< this->getCols(); j++)
        {
            float element = this->get(i,j) + m.get(i,j);
            result.set(i,j,element);
        }
    }

    return result;
}

Matrix Matrix::subtract(Matrix& m)
{
   Matrix result(m.getRows(),m.getCols());
   m = m.multiply(-1);
   result = this->add(m);

   return result;
}

Matrix Matrix::multiply(float nr)
{
    Matrix result(this->getRows(),this->getCols());

    for(int i = 0; i<this->getRows();i++)
    {
        for(int j = 0; j<this->getCols();j++)
        {
            float element = this->get(i,j) * nr;
            result.set(i,j,element);
        }
    }

    return result;
}

Matrix Matrix::multiply(Matrix& m)
{
    //A rows -- B cols -> result matrix;
    if(this->getCols() != m.getRows())
    {
        throw std::invalid_argument("in matrix multiplication the rows of A must equal the length of cols of B");
    }

    Matrix result(this->getRows(),m.getCols());

    for(int i = 0; i < this->getRows(); i++)
    {
        
        for(int j = 0; j < m.getCols(); j++)
        {
            float element = 0;

            for(int t = 0; t < this->getCols(); t++)
                {element += this->get(i,t) * m.get(t,i);}

            result.set(i,j,element);
        }

        
    }
    return result;
}

Matrix Matrix::divide(float nr)
{
    Matrix result(this->getRows(),this->getCols());

    for(int i = 0; i<this->getRows();i++)
    {
        for(int j = 0; j<this->getCols();j++)
        {
            float element = this->get(i,j) / nr;
            result.set(i,j,element);
        }
    }

    return result;
}

Matrix Matrix::transpose()
{
    Matrix result(this->getCols(),this->getRows()); // transposed matrix;

    for(int i = 0; i < getRows(); i++)
        {
            for(int j = 0; j< getCols(); j++)
            {
                result.set(j,i,this->get(i,j));
            }
        }
    return result;
}

//set and get

void Matrix::set(int row, int col,float element)
{
    if (row < 0 || col < 0 || row >= this->getRows() || col >= getCols())
        throw std::invalid_argument("wrong argument");
    else
        matrix[row][col] = element;
}

float Matrix::get(int row, int col)
{
    if (row < 0 || col < 0 || row >= this->getRows() || col >= getCols())
        throw std::invalid_argument("wrong argument");
    else
        return matrix[row][col];
}



//getCols/Rows
int Matrix::getCols()
{
    return m_cols;
}


int Matrix::getRows()
{
    return m_rows;
}

void Matrix::print()
{
    for(auto i : matrix)
    {
        for(auto j : i)
        {
            std::cout<<j<<" ";
        }
        std::cout<<"\n";
    }
}