//Activation.h
#ifndef ACTIVATION_H
#define ACTIVATION_H

#define ERR_INVALID_SIZE            "Error: matrix size invalid"
#define ERR_INVALID_ADDITION        "Error: cannot add matrices of diff sizes"
#define ERR_INVALID_MULTIPLICATION  "Error: cannot add matrices of diff sizes"
#define ERR_INVALID_INDEX           "Error: invalid index"
#define ERR_INVALID_FILE            "Error: file is invalid"

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
