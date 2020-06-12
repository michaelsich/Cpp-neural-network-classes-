//Activation.h
#ifndef ACTIVATION_H
#define ACTIVATION_H

#include <cmath>
#include "Matrix.h"

/**
 * @enum ActivationType
 * @brief Indicator of activation function.
 */
enum ActivationType
{
    Relu,
    Softmax
};

class Activation
{
    public:
        Activation(ActivationType actType = Relu);
        ActivationType getActivationType() const;
        Matrix operator() (const Matrix& inputMtx) const;

    private:
        ActivationType actType;

        void performRelu(Matrix& oMatrix) const;
        void performSoftmax(Matrix& oMatrix) const;
};

#endif //ACTIVATION_H
