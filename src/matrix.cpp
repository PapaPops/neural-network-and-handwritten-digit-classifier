#include "./matrix.h"





Matrix::Matrix(const Matrix& m)
{

    this->m_cols = m.getCols();
    this->m_rows = m.getRows();

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


Matrix Matrix::add(Matrix& m) const
{
    if(m_rows != m.getRows() || m_cols != m.getCols())
        throw std::invalid_argument("the matrix that was passed as an argument doesn't have the same row anc col length as the matrix object");
    
    Matrix result(m_rows,m_cols);

    for(int i = 0; i < m_rows; i++)
    {
        for(int j = 0; j< m_cols; j++)
        {
            float element = this->get(i,j) + m.get(i,j);
            result.set(i,j,element);
        }
    }

    return result;
}

Matrix Matrix::subtract(Matrix& m) const
{
   Matrix result(m.getRows(),m.getCols());
   m = m.multiply(-1);
   result = this->add(m);

   return result;
}

Matrix Matrix::multiply(float nr) const
{
    Matrix result(m_rows,m_cols);

    for(int i = 0; i<m_rows;i++)
    {
        for(int j = 0; j<m_cols;j++)
        {
            float element = this->get(i,j) * nr;
            result.set(i,j,element);
        }
    }

    return result;
}

Matrix Matrix::multiply(Matrix& m) const
{
    //A rows -- B cols -> result matrix;
    if(m_cols != m.getRows())
    {
        throw std::invalid_argument("in matrix multiplication the cols of A must equal the length of rows of B ");
    }

    Matrix result(m_rows,m.getCols());

    for(int i = 0; i < m_rows; i++)
    {
        
        for(int j = 0; j < m.getCols(); j++)
        {
            float element = 0;

            for(int t = 0; t < m_cols ; t++)
                {element += matrix[i][t] * m.get(t,j);}

            result.set(i,j,element);
        }

        
    }
    return result;
}

Matrix Matrix::divide(float nr) const
{
    Matrix result(m_rows,m_cols);

    for(int i = 0; i<m_rows;i++)
    {
        for(int j = 0; j<m_cols;j++)
        {
            float element = this->get(i,j) / nr;
            result.set(i,j,element);
        }
    }

    return result;
}

Matrix Matrix::transpose() const
{
    Matrix result(m_cols,m_rows); // transposed matrix;

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
    if (row < 0 || col < 0 || row >= m_rows || col >= m_cols)
        throw std::invalid_argument("wrong argument set");
    else
        matrix[row][col] = element;
}

float Matrix::get(int row, int col) const
{
    if (row < 0 || col < 0 || row >= m_rows || col >= m_cols)
        {
            throw std::invalid_argument("wrong argument get");   
        }
    else
        return this->matrix[row][col];
}



//getCols/Rows
int Matrix::getCols() const
{
    return m_cols;
}


int Matrix::getRows() const
{
    return m_rows;
}

void Matrix::print() const
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

//randomize 
void Matrix::randomize()
{
    for(int i = 0; i < m_rows; i++)
    {
        for(int j = 0; j < m_cols; j++)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            float element = ((float)rand() / RAND_MAX) * 2 - 1; // -1 - 1
            this->set(i,j,element);
        }
    }
}

