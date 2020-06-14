//
// Created by michael on 13/06/2020.
//

#include "MlpNetwork.h"

MlpNetwork::MlpNetwork(const Matrix* weights, const Matrix* biases)
{
    if (weights == nullptr || biases == nullptr)
    {
        std::cerr << ERR_INVALID_INPUT << std::endl;
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < MLP_SIZE; ++i)
    {
        this->weights[i]    = weights[i];
        this->biases[i]     = biases[i];
    }
}

Digit MlpNetwork::operator()(Matrix &picture)
{
    Digit calculatedResult = {0, 0};
    Activation relu         = Activation(Relu),
               softmax      = Activation(Softmax);
    Dense      allLayers[]  = new Dense[MLP_SIZE];

    for (int i = 0; i < MLP_SIZE - 1; ++i)
    {
        (allLayers[i]) = new Dense(weights[i], biases[i], relu);
    }

    //last layer - apply softmax
    allLayers[MLP_SIZE - 1] = new Dense(weights[MLP_SIZE - 1],
                                        biases[MLP_SIZE - 1],
                                        softmax);

    Matrix& = a

}

Matrix& MlpNetwork::applyLayersOnPic(Matrix &pic, Dense* allLayers)
{
    // first layers
    Matrix out = allLayers[0](pic);

    for (int i = 1; i < MLP_SIZE - 1; ++i)
    { // all Relu layers
        out = allLayers[i](out);
    }

    // softmax
    return allLayers[MLP_SIZE - 1](out);
}
