//
// Created by michael on 12/06/2020.
//

#include "Activation.h"
/**
 * @brief activation class
 */
Activation::Activation(ActivationType type)
{
    this->actType = type;
}

/**
 * @brief getter of activation type
 */
ActivationType Activation::getActivationType() const
{
    return this->actType;
}

/**
 * @brief operator ()
 */
Matrix Activation::operator()(const Matrix& inputMtx) const
{
    Matrix productMatrix = Matrix(inputMtx);
    switch (actType)
    {
        case Relu:
            Activation::performRelu(productMatrix);
            break;
        case Softmax:
            Activation::performSoftmax(productMatrix);
            break;
    }
    return productMatrix;
}

/**
 * @brief algo of Relu function on the matrix
 */
void Activation::performRelu(Matrix &oMatrix) const
{
    for (int i = 0; i < oMatrix.getRows() * oMatrix.getCols(); ++i)
    {
        if (oMatrix[i] < 0)
        {
            oMatrix[i] = 0;
        }
    }
}

/**
 * @brief algo of Softmax function on the matrix
 */
void Activation::performSoftmax(Matrix &oMatrix) const
{
    float sumOfExpInPowerOfCoords = 0;
    for (int i = 0; i < oMatrix.getCols() * oMatrix.getRows(); ++i)
    {
        sumOfExpInPowerOfCoords += std::exp(oMatrix[i]);
    }
    for (int i = 0; i < oMatrix.getCols() * oMatrix.getRows(); ++i)
    {
        oMatrix[i] = (std::exp(oMatrix[i])) * (1 / sumOfExpInPowerOfCoords);
    }
}

/**
 * @brief operator = of this class
 */
Activation& Activation::operator=(const Activation& rhs)
{
    this->actType = rhs.actType;
    return *this;
}
