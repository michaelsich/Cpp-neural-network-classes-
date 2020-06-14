//
// Created by michael on 12/06/2020.
//

#include "Dense.h"

Dense::Dense(Matrix& weigth, Matrix& bias, Activation actFunc)
{
    weigth = weigth;
    bias = bias;
    actFunc = actFunc;
}

Dense::Dense(const Dense &dense)
{
    weigth = dense.weigth;
    actFunc = dense.actFunc;
    bias = dense.bias;
}

Dense::Dense()
= default;

