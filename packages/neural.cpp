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

std::vector<double> CreateWeightLayer(int size)
{
    std::vector<double> weight_layer;
    std::srand(std::time(nullptr));

    for (int i = 0; i < size; ++i)
    {
        weight_layer.push_back((double)(std::rand() % 100 + 1) * 0.1 / 100);
    }
    return weight_layer;
}

int PredictFunction(double value, float threshold = 0.5)
{
    return (value >= threshold) ? 1 : 0;
}

void AdjustWeights(std::vector<double> &weight_layer,
                   std::vector<std::vector<int>> &input_data,
                   int answer,
                   double prediction,
                   float learning_rate = 0.1)
{
    double error = answer - prediction;
    for (int i = 0; i < input_data.size(); ++i)
    {
        for (int j = 0; j < input_data.size(); ++j)
        {
            if (input_data[i][j])
                weight_layer[i + j] += learning_rate * error * input_data[i][j];
        }
    }
}

double Predict(std::vector<double> &weight_layer,
               std::vector<std::vector<int>> &input_data)
{
    double weighted_sum = 0;

    for (int i = 0; i < input_data.size(); ++i)
    {
        for (int j = 0; j < input_data.size(); ++j)
        {
            weighted_sum += input_data[i][j] * weight_layer[i + j];
        }
    }

    return weighted_sum;
}

std::string GetResult(std::vector<double> &weight_layer,
                      std::vector<std::vector<int>> &input_data)
{
    double weighted_sum = Predict(weight_layer, input_data);
    int prediction = PredictFunction(weighted_sum);
    std::cout << "с Вероятностью " << weighted_sum << "Это ";
    return OutputData::getValue(prediction);
}

std::string Traning(std::vector<double> &weight_layer,
                    std::vector<std::vector<int>> &input_data,
                    int answer)
{
    double weighted_sum = Predict(weight_layer, input_data);
    int prediction = PredictFunction(weighted_sum);
    AdjustWeights(weight_layer, input_data, answer, prediction);
    return OutputData::getValue(prediction);
}
