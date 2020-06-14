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
    Activation relu         = Activation(Relu),
               softmax      = Activation(Softmax);
    Dense allLayers[MLP_SIZE];

    for (int i = 0; i < MLP_SIZE - 1; ++i)
    {
        (allLayers[i]) = Dense(weights[i], biases[i], relu);
    }

    //last layer - apply softmax
    allLayers[MLP_SIZE - 1] = Dense(weights[MLP_SIZE - 1],
                                        biases[MLP_SIZE - 1],
                                        softmax);

    Matrix out = Matrix();
    out = applyLayersOnPic(picture, allLayers, out);

    Digit calculatedResult = findMaxProbResult(out);

}

Matrix& MlpNetwork::applyLayersOnPic(Matrix &pic, Dense* allLayers, Matrix& out)
{
    // first layers
    out = allLayers[0](pic);
    for (int i = 1; i < MLP_SIZE - 1; ++i)
    { // all Relu layers
        out = allLayers[i](out);
    }

    // softmax
    //TODO: will leak?
    Matrix& temp = out;
    out = allLayers[MLP_SIZE - 1](out);
    return out;
}

Digit MlpNetwork::findMaxProbResult(const Matrix &lastOutput) const
{
    float            maxProb = -1;
    unsigned int     mostProbableNum = -1;

    for (int i = 0; i < lastOutput.getRows(); ++i)
    {
        if (lastOutput[i] > maxProb)
        {
            maxProb = lastOutput[i];
            mostProbableNum = i;
        }
    }
    return Digit{mostProbableNum, maxProb};
}
