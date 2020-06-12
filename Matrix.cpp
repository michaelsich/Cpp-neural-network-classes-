//
// Created by michael on 12/06/2020.
//

#include "Matrix.h"

Matrix::Matrix()
{
    matrixData.cols = 1;
    matrixData.rows = 1;
    matrix = new float[DEFAULT_CTOR_SIZE];
    matrix[0] = 0;
}

Matrix::Matrix(int rows, int cols)
{
    //TODO: add rows cols edge cases chcek - stderr output
    matrixData.cols = cols;
    matrixData.rows = rows;
    matrix = new float[rows * cols]{0};
}

Matrix::Matrix(const Matrix &m)
{
    matrixData.rows = m.matrixData.rows;
    matrixData.cols = m.matrixData.cols;
    matrix = new float[matrixData.rows * matrixData.cols];

    for (int i = 0; i < matrixData.rows * matrixData.cols; ++i)
    {
        matrix[i] = m.matrix[i];
    }
}

Matrix& Matrix::vectorize()
{
    this->matrixData.rows = this->matrixData.rows * this->matrixData.cols;
    this->matrixData.cols = 1;

    return *this;
}

void Matrix::plainPrint() const
{
    for (int i = 0; i < this->matrixData.rows; ++i)
    {
        for (int j = 0; j < this->matrixData.cols; ++j)
        {
            std::cout << (*this)(i,j) << " ";
        }
        std::cout << std::endl;
    }
}

Matrix& Matrix::operator= (const Matrix& rhs)
{
    if (this == &rhs)
    { // already the same
        return *this;
    }

    delete[] this->matrix;
    *this = Matrix(rhs);

    return *this;
}

Matrix& Matrix::operator+= (const Matrix &rhs)
{
    if ((rhs.matrixData.cols != this->matrixData.cols) ||
        (rhs.matrixData.rows != this->matrixData.rows))
    {
        //TODO: out error
    }

    for (int i = 0; i < matrixData.rows * matrixData.cols; ++i)
    {
        matrix[i] += rhs.matrix[i];
    }
    return *this;

}

Matrix Matrix::operator+ (const Matrix &rhs)
{
    if ((rhs.matrixData.cols != this->matrixData.cols) ||
        (rhs.matrixData.rows != this->matrixData.rows))
    {
        //TODO: out error
    }

    Matrix newMat = Matrix(matrixData.rows, matrixData.cols);
    for (int i = 0; i < matrixData.rows * matrixData.cols; ++i)
    {
        newMat.matrix[i] = this->matrix[i] + rhs.matrix[i];
    }
    return newMat;
}

Matrix Matrix::operator* (const Matrix &rhs) const
{
    if (matrixData.cols != rhs.matrixData.rows)
    {
        //TODO: error
    }

    int     newCols = rhs.getCols(),
            newRows = matrixData.rows;
    float   sum     = 0;

    Matrix multiMtx = Matrix(newRows, newCols);

    for (int i = 0; i < matrixData.rows; ++i)
    { // rows of *this
        for (int j = 0; j < rhs.matrixData.rows; ++j)
        {   // rows of rhs

            sum = 0;
            for (int k = 0; k < matrixData.cols; ++k)
            {   // cols of *this
                sum += (*this)(i,k) * rhs(k,i);
            }
            multiMtx.matrix[(i * newCols) + j] = sum;
        }
    }
    return multiMtx;
}

Matrix Matrix::operator*(const float scalar) const
{
    Matrix newMtx = Matrix(matrixData.rows, matrixData.cols);

    for (int i = 0; i < matrixData.rows * matrixData.cols; ++i)
    {
        newMtx.matrix[i] = (*this)[i] * scalar;
    }
    return newMtx;
}

Matrix operator*(const float scalar, const Matrix &mtx)
{
    Matrix newMtx = Matrix(mtx.matrixData.rows, mtx.matrixData.cols);

    for (int i = 0; i < mtx.matrixData.rows * mtx.matrixData.cols; ++i)
    {
        newMtx.matrix[i] = mtx[i] * scalar;
    }
    return newMtx;
}

float Matrix::operator() (int i, int j) const
{
    if (i < 0 || j < 0)
    {
        //TODO: throw error
    }
    return this->matrix[(i * matrixData.cols) + j];
}

std::ostream& operator<< (std::ostream& oStream, const Matrix& mtx)
{
    for (int i = 0; i < mtx.matrixData.rows; ++i)
    {
        for (int j = 0; j < mtx.matrixData.cols; ++j)
        {
            if (mtx(i, j) <= ACTIVE_THRESHOLD)
            {
                oStream << DISABLED_PXL;
            }
            else
            {
                oStream << ENABLED_PXL;
            }
        }
        oStream << std::endl;
    }
    return oStream;
}

std::ifstream& operator>> (std::ifstream& iStream, Matrix& mtx)
{
    //TODO: I think I didnt get how to implement it - manual says use .Read ??
    for (int i = 0; i < mtx.matrixData.rows * mtx.matrixData.cols; ++i)
    {
        if (iStream.good())
        {
            iStream >> mtx.matrix[i];
        }
        else
        {
            //TODO: Handle error
        }
    }
    return iStream;
}