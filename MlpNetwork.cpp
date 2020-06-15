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

    for (int i = 0; i < MLP_SIZE; ++i)
    {
        if (i == MLP_SIZE - 1)
        {
            Dense temp = Dense(weights[i], biases[i], softmax);
            picture = softmax(temp(picture));
        }
        else
        {
            Dense temp = Dense(weights[i], biases[i], relu);
            picture = relu(temp(picture));
        }
    }
    return findMaxProbResult(picture);

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
