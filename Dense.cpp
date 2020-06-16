//
// Created by michael on 12/06/2020.
//

#include "Dense.h"

/**
 * @brief ctor for dense object in mlp network
 * @param weigth layers weight matri x
 * @param bias matrix of bias
 * @param actFunc activation function of this layer
 */
Dense::Dense(Matrix& weigth, Matrix& bias, Activation actFunc)
{
    this->weigth = weigth;
    this->bias = bias;
    this->actFunc = actFunc;
}

/**
 * @brief copy ctor
 */
Dense::Dense(const Dense &dense)
{
    weigth = dense.weigth;
    actFunc = dense.actFunc;
    bias = dense.bias;
}

/**
 * @brief operator = of dense
 * @param rhs right side handside
 */
Dense &Dense::operator=(const Dense &rhs)
{
    this->weigth  = rhs.weigth;
    this->bias    = rhs.bias;
    this->actFunc = rhs.actFunc;
    return (*this);
}

/**
 * @brief default ctor
 */
Dense::Dense()
= default;

