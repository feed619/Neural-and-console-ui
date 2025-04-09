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
        if (key == 0)
            return value_0;
        else if (key == 1)
            return value_x;
        else
            return "Не смог определить!";
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
                   int correct_layer_index,
                   float learning_rate = 0.01)
{
    for (int index = 0; index < matrix_weight_layer.size(); ++index)
    {

        int error;
        if (index == correct_layer_index)
            error = 1 - vector_prediction[index];
        else
            error = 0 - vector_prediction[index];

        for (int i = 0; i < input_data.size(); ++i)
        {
            for (int j = 0; j < input_data.size(); ++j)
            {
                if (input_data[i][j])
                    matrix_weight_layer[index][i * input_data.size() + j] += learning_rate * error * input_data[i][j];
            }
        }
    }
}

std::vector<double> GetWeightedSum(std::vector<std::vector<double>> &matrix_weight_layer,
                                   std::vector<std::vector<int>> &input_data)
{
    std::vector<double> vector_weighted_sum;
    int a = 0;
    for (auto weight_layer : matrix_weight_layer)
    {
        double weighted_sum = 0;
        for (int i = 0; i < input_data.size(); ++i)
        {
            for (int j = 0; j < input_data.size(); ++j)
            {
                if (input_data[i][j])
                    weighted_sum += (double)input_data[i][j] * weight_layer[i * input_data.size() + j];
            }
        }
        std::cout << "W=> " << a << "   " << weighted_sum << "\n";
        vector_weighted_sum.push_back(weighted_sum);
        ++a;
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
    std::vector<double> vector_weighted_sum = GetWeightedSum(matrix_weight_layer, input_data);
    std::vector<int> vector_prediction;
    int max_index = 0;
    int correct_index = -1;
    int count_prediction = 0;
    int i = 0;
    for (double weighted_sum : vector_weighted_sum)
    {
        if (vector_weighted_sum[max_index] < vector_weighted_sum[i])
            max_index = i;
        int prediction = PredictFunction(weighted_sum);
        if (prediction)
        {
            count_prediction++;
            correct_index = i;
        }
        vector_prediction.push_back(prediction);
        ++i;
    }
    std::cout << "\n";
    if (count_prediction > 1)
    {
        correct_index = -1;
    }
    return OutputData::getValue(correct_index);
}

void Traning(std::vector<std::vector<double>> &matrix_weight_layer,
             std::vector<std::vector<int>> &input_data,
             int answer)
{
    std::vector<double> vector_weighted_sum = GetWeightedSum(matrix_weight_layer, input_data);
    std::vector<int> vector_prediction;

    int i = 0;
    for (double weighted_sum : vector_weighted_sum)
    {
        int prediction = PredictFunction(weighted_sum);
        vector_prediction.push_back(prediction);
        ++i;
    }
    AdjustWeights(matrix_weight_layer, input_data, vector_prediction, answer);
    std::vector<double> vector_weighted_sum_2 = GetWeightedSum(matrix_weight_layer, input_data);
}
