#include <vector>
#include <iostream>

void NoiseRemoval(std::vector<std::vector<int>> &matrix, int width, int height)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (matrix[i][j] == 1)
            {
                if (j + 1 <= width and i + 1 <= height)
                    if ((matrix[i][j + 1] == 1) or (matrix[i - 1][j] == 1) or (matrix[i + 1][j + 1] == 1))
                    {
                        j += 1;
                        i += 1;
                        continue;
                    }
                    else
                    {
                        matrix[i][j] = 0;
                    }
            }
        }
    }
}

void ClearMatrix(std::vector<std::vector<int>> &matrix, int width, int height)
{
    for (int i = 0; i < height; i++)

    {
        for (int j = 0; j < width; j++)

        {
            matrix[i][j] = 0;
        }
    }
}

void printMatrix(std::vector<std::vector<int>> read_matrix)
{

    std::vector<float> new_vector;
    for (auto vector : read_matrix)
    {
        for (auto number : vector)
        {
            std::cout << number << " ";
        }
        std::cout << "\n";
    }
}
