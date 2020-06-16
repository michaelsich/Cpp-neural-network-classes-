//
// Created by michael on 12/06/2020.
//

#include "Matrix.h"
/**
 * @brief def ctor
 */
Matrix::Matrix()
{
    matrixData.cols = 1;
    matrixData.rows = 1;
    matrix = new float[DEFAULT_CTOR_SIZE];
    matrix[0] = 0;
}
/**
 * @brief ctor
 * @param rows rows
 * @param cols cols
 */
Matrix::Matrix(int rows, int cols)
{
    if (rows <= 0 || cols <= 0)
    {   // error
        std::cerr << ERR_INVALID_SIZE << std::endl;
        exit(EXIT_FAILURE);
    }
    matrixData.cols = cols;
    matrixData.rows = rows;
    matrix = new float[rows * cols]{0};

}
/**
 * @brief copy ctor
 * @param m matrix (const)
 */
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
/**
 * @brief turns matrix into a single column vector
 * @return ref to the matrix
 */
Matrix& Matrix::vectorize()
{
    this->matrixData.rows = this->matrixData.rows * this->matrixData.cols;
    this->matrixData.cols = 1;

    return *this;
}

/**
 * @brief strange way to print matrix elements
 */
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

/**
 * @brief operator = of matrix class
 * @param rhs right hand side
 * @return ref to new matrix
 */
Matrix& Matrix::operator= (const Matrix& rhs)
{
    if (this == &rhs)
    { // already the same
        return *this;
    }

    delete[] this->matrix;
    matrixData.rows = rhs.matrixData.rows;
    matrixData.cols = rhs.matrixData.cols;
    matrix = new float[matrixData.rows * matrixData.cols];

    for (int i = 0; i < matrixData.rows * matrixData.cols; ++i)
    {
        matrix[i] = rhs.matrix[i];
    }

    return *this;
}

/**
 * @brief operator +=
 */
Matrix& Matrix::operator+= (const Matrix &rhs)
{
    if ((rhs.matrixData.cols != this->matrixData.cols) ||
        (rhs.matrixData.rows != this->matrixData.rows))
    {
        std::cerr << ERR_INVALID_ADDITION << std::endl;
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < matrixData.rows * matrixData.cols; ++i)
    {
        matrix[i] += rhs.matrix[i];
    }
    return *this;

}

/**
 * @brief opertor +
 */
Matrix Matrix::operator+ (const Matrix &rhs) const
{
    if ((rhs.matrixData.cols != this->matrixData.cols) ||
        (rhs.matrixData.rows != this->matrixData.rows))
    {
        std::cerr << ERR_INVALID_ADDITION << std::endl;
        exit(EXIT_FAILURE);
    }

    Matrix newMat(matrixData.rows, matrixData.cols);
    for (int i = 0; i < matrixData.rows * matrixData.cols; ++i)
    {
        newMat.matrix[i] = this->matrix[i] + rhs.matrix[i];
    }
    return newMat;
}

/**
 * @brief opertor * with matrix
 */
Matrix Matrix::operator* (const Matrix &rhs) const
{
    if (matrixData.cols != rhs.matrixData.rows)
    {
        std::cerr << ERR_INVALID_MULTIPLICATION << std::endl;
        exit(EXIT_FAILURE);
    }

    int     newCols = rhs.getCols(),
            newRows = matrixData.rows;
    float   sum     = 0;

    Matrix multiMtx = Matrix(newRows, newCols);

    for (int i = 0; i < matrixData.rows; ++i)
    { // rows of *this
        for (int j = 0; j < rhs.matrixData.cols; ++j)
        {   // cols of rhs
            sum = 0;
            for (int k = 0; k < matrixData.cols; ++k)
            {   // cols of *this
                sum += (*this)(i,k) * rhs(k,j);
            }
            multiMtx.matrix[(i * newCols) + j] = sum;
        }
    }
    return multiMtx;
}

/**
 * @brief opertor * for scalar (scalar is rhs)
 */
Matrix Matrix::operator*(const float scalar) const
{
    Matrix newMtx = Matrix(matrixData.rows, matrixData.cols);

    for (int i = 0; i < matrixData.rows * matrixData.cols; ++i)
    {
        newMtx.matrix[i] = (*this)[i] * scalar;
    }
    return newMtx;
}

/**
 * @brief opertor * for scalar (scalar is rhs)
 */
Matrix operator*(const float scalar, const Matrix &mtx)
{
    Matrix newMtx = Matrix(mtx.matrixData.rows, mtx.matrixData.cols);

    for (int i = 0; i < mtx.matrixData.rows * mtx.matrixData.cols; ++i)
    {
        newMtx.matrix[i] = mtx[i] * scalar;
    }
    return newMtx;
}

/**
 * @brief opertor ()
 */
float Matrix::operator() (int i, int j) const
{
    if (i < 0 || j < 0 || i >= matrixData.rows || j >= matrixData.cols)
    {
        std::cerr << ERR_INVALID_INDEX << " i: " << i << " j: " << j << std::endl;
        exit(EXIT_FAILURE);
    }
    return this->matrix[(i * matrixData.cols) + j];
}

/**
 * @brief opertor()
 * return a refrence
 */
float& Matrix::operator()(int i, int j)
{
    if (i < 0 || j < 0 || i >= matrixData.rows || j >= matrixData.cols)
    {
        std::cerr << ERR_INVALID_INDEX << " i: " << i << " j: " << j << std::endl;
        exit(EXIT_FAILURE);
    }
    return (matrix[(i * matrixData.cols) + j]);
}

/**
 * @brief prints the current matrix to the given oStream
 * @param oStream output stream
 * @param mtx matrix
 * @return the oStream
 */
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

/**
 * @brief inputs the matrix values from the given iStream
 * @param iStream random input stream (file)
 * @param mtx matrix to input into
 * @return the iStream
 */
std::istream& operator>> (std::istream& iStream, Matrix& mtx)
{
    char* temp = (char*)malloc(sizeof(float));
    for (int i = 0; i < mtx.matrixData.rows * mtx.matrixData.cols; ++i)
    {
        if (iStream.good())
        {
            iStream.read(temp,sizeof(float));
            mtx[i] = *(float *)temp;
        }
        else
        {
            std::cerr << ERR_INVALID_FILE << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    free(temp);
    if (iStream.peek() != EOF)
    {
        std::cerr << ERR_INVALID_FILE << std::endl;
        exit(EXIT_FAILURE);
    }
    return iStream;
}

/**
 * @brief getter for the element at the i'th index in the matrix
 */
float Matrix::operator[](int i) const
{
    if (i < 0 || i >= matrixData.cols * matrixData.rows)
    {
        std::cerr << ERR_INVALID_INDEX << " i: " << i << std::endl;
        exit(EXIT_FAILURE);
    }
    return matrix[i];
}
/**
 * @brief getter for at the i'th index refrence in the matrix
 */
float &Matrix::operator[](int i)
{
    if (i < 0 || i >= matrixData.cols * matrixData.rows)
    {
        std::cerr << ERR_INVALID_INDEX << " i: " << i << std::endl;
        exit(EXIT_FAILURE);
    }
    return matrix[i];
}


