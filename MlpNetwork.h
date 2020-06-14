//MlpNetwork.h

#ifndef MLPNETWORK_H
#define MLPNETWORK_H

#include "Matrix.h"
#include "Digit.h"
#include "Dense.h"

#define MLP_SIZE 4
#define ERR_INVALID_INPUT "Error: Invalid input!"

const MatrixDims imgDims = {28, 28};
const MatrixDims weightsDims[] = {{128, 784}, {64, 128}, {20, 64}, {10, 20}};
const MatrixDims biasDims[]    = {{128, 1}, {64, 1}, {20, 1},  {10, 1}};


class MlpNetwork
{
    public:
        MlpNetwork(const Matrix* weights, const Matrix* biases);
        Digit operator() (Matrix& picture);

private:
        Matrix  weights[MLP_SIZE],
                biases[MLP_SIZE];
        Matrix& applyLayersOnPic(Matrix& pic, Dense* allLayers, Matrix& out);
        Digit findMaxProbResult(const Matrix& lastOutput) const;

};



#endif // MLPNETWORK_H
