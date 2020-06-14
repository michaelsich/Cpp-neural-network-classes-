//
// Created by michael on 12/06/2020.
//
#ifndef DENSE_H
#define DENSE_H

#include "Activation.h"

class Dense
{
    public:
        Dense(Matrix& weigth, Matrix& bias, Activation actFunc);

        inline const Matrix&     getWeights()    const {return weigth;}
        inline const Matrix&     getBias()       const {return bias;}
        inline const Activation& getActivation() const {return actFunc;}

        inline Matrix operator() (const Matrix& input) const {return (input * weigth) + bias;}

    private:
        Matrix weigth;
        Matrix bias;
        Activation actFunc;
};


#endif //DENSE_H
