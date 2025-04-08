#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iostream>

struct OutputData
{
    inline static const std::string value_x = "X";
    inline static const std::string value_0 = "0";

    static std::string getValue(int key)
    {
        return key ? value_x : value_0;
    }
};

std::vector<std::vector<double>> CreateWeightLayer(int count, int size)
{
    std::vector<std::vector<double>> matrix_weight_layer;
    std::srand(std::time(nullptr));

    for (int index = 0; index < count; ++index)
    {
        std::vector<double> weight_layer;
        for (int i = 0; i < size; ++i)
        {
            weight_layer.push_back((double)(std::rand() % 199 - 99) * 0.1 / 100);
        }
        matrix_weight_layer.push_back(weight_layer);
    }
    return matrix_weight_layer;
}

int PredictFunction(double value, float threshold = 0)
{
    return (value > threshold) ? 1 : 0;
}

void AdjustWeights(std::vector<std::vector<double>> &matrix_weight_layer,
                   std::vector<std::vector<int>> &input_data,
                   std::vector<int> vector_prediction,
                   int answer,
                   float learning_rate = 0.1)
{
    for (int index = 0; index < matrix_weight_layer.size(); ++index)
    {
        int error;
        if (index == answer)
            error = 1 - vector_prediction[index];
        else
            error = 0 - vector_prediction[index];

        for (int i = 0; i < input_data.size(); ++i)
        {
            for (int j = 0; j < input_data[i].size(); ++j)
            {
                matrix_weight_layer[index][i + j] += learning_rate * error * input_data[i][j];
            }
        }
    }
}

std::vector<double> Predict(std::vector<std::vector<double>> &matrix_weight_layer,
                            std::vector<std::vector<int>> &input_data)
{
    std::vector<double> vector_weighted_sum;
    for (auto weight_layer : matrix_weight_layer)
    {
        double weighted_sum = 0;
        for (int i = 0; i < input_data.size(); ++i)
        {
            for (int j = 0; j < input_data.size(); ++j)
            {
                weighted_sum += input_data[i][j] * weight_layer[i + j];
            }
        }
        vector_weighted_sum.push_back(weighted_sum);
    }

    return vector_weighted_sum;
}
int GetCorrectPosition(std::vector<int> &vector_prediction)
{
    int i = 0;
    for (int prediction : vector_prediction)
    {
        if (prediction)
            return i;
        ++i;
    }
    return -1;
}
std::string GetResult(std::vector<std::vector<double>> &matrix_weight_layer,
                      std::vector<std::vector<int>> &input_data)
{
    std::vector<double> vector_weighted_sum = Predict(matrix_weight_layer, input_data);
    std::vector<int> vector_prediction;
    for (double weighted_sum : vector_weighted_sum)
    {
        int prediction = PredictFunction(weighted_sum);
        vector_prediction.push_back(prediction);
    }
    int correct_position = GetCorrectPosition(vector_prediction);
    return OutputData::getValue(correct_position);
}

void Traning(std::vector<std::vector<double>> &matrix_weight_layer,
             std::vector<std::vector<int>> &input_data,
             int answer)
{
    std::vector<double> vector_weighted_sum = Predict(matrix_weight_layer, input_data);
    std::vector<int> vector_prediction;
    for (double weighted_sum : vector_weighted_sum)
    {
        int prediction = PredictFunction(weighted_sum);
        vector_prediction.push_back(prediction);
    }
    int correct_position = GetCorrectPosition(vector_prediction);

    if (correct_position != answer)
        AdjustWeights(matrix_weight_layer, input_data, vector_prediction, answer);
}
