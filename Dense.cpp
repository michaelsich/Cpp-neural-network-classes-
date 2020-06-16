//
// Created by michael on 12/06/2020.
//

#include "Dense.h"

Dense::Dense(Matrix& weigth, Matrix& bias, Activation actFunc)
{
    this->weigth = weigth;
    this->bias = bias;
    this->actFunc = actFunc;
}

Dense::Dense(const Dense &dense)
{
    weigth = dense.weigth;
    actFunc = dense.actFunc;
    bias = dense.bias;
}

Dense &Dense::operator=(const Dense &rhs)
{
    this->weigth  = rhs.weigth;
    this->bias    = rhs.bias;
    this->actFunc = rhs.actFunc;
    return (*this);
}

Dense::Dense()
= default;

