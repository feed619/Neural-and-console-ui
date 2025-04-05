#include <vector>
#include <iostream>
#include "Tree.cpp"

void NoiseRemoval(std::vector<std::vector<int>> &matrix, int width, int height)
{

    // matrix[1][1] = 1;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (matrix[i][j] == 1)
            {
                // matrix[2][2] = 1;
                // std::cout << (matrix[i][j + 1] == 1) << (matrix[i - 1][j] == 1) << (matrix[i + 1][j + 1] == 1) << "\n";
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

void isX(std::vector<std::vector<int>> &matrix, int width, int height)
{
    float float_x = 0;
    int streak = 0;
    int streak_bad = 0;
    int count_fill_pixels = 0;
    int j = 0;
    int i = 0;
first:
    for (; i < height;)

    {
        if (i >= height)
        {
            break;
        }

    second:
        for (; j < width;)

        {
            std::cout << i << j << "\n";
            if (j >= width)
            {
                break;
            }
            if (matrix[i][j] == 1)
            {
                count_fill_pixels++;
                if (i + 1 >= height)
                {
                    i++;
                    float_x += 1;
                    break;
                }
                if (j + 1 >= width)
                {
                    j++;
                    float_x += 1;
                    break;
                }
                if (matrix[i][j + 1] == 1)
                {
                    float_x += 0.5;
                    // i++;
                    j++;
                }
                else if (matrix[i + 1][j] == 1)
                {
                    float_x += 0.5;
                    i++;
                    j++;
                }
                else if (matrix[i + 1][j + 1] == 1)
                {
                    std::cout << "dadasd\n";
                    float_x += 1;
                    i += 1;
                    j++;
                }
                else
                {
                    float_x -= 1;
                    streak_bad++;
                    if (streak_bad == 3)
                    {
                        std::cout << float_x << "\n";
                        streak_bad = 0;
                        float_x = 0;
                    }
                    j++;
                    i++;
                    continue;
                }
                goto second;
            }

            else
            {
                j++;
                if (j == width - 1)
                {
                    i++;
                    goto first;
                }
            }
        }
    }
    std::cout << float_x / count_fill_pixels << "\n";
}

std::vector<std::vector<int>> DifferentTree(std::vector<std::vector<int>> &matrix, int width, int height)
{

    std::vector<std::vector<int>> read_matrix;
    for (int i = 0; i < height; i++)
    {

        std::vector<int> read_vector;

        int count_pixels = ((i + 1) * 2 - 1);
        std::cout << count_pixels << " ";
        for (int j = 0; j < count_pixels; j++)

        {

            // std::cout << j << " ";
            if (j <= i)
            {
                // std::cout << j << " ";
                read_vector.push_back(matrix[i][j]);
            }
            else
            {
                read_vector.push_back(matrix[count_pixels - j - 1][i]);

                // std::cout << count_pixels - j - 1 << "-" << i << " ";
            }

            // std::cout << j;
        }
        read_matrix.push_back(read_vector);
        std::cout << "\n";
    }
    return read_matrix;
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
int defineX(std::vector<Tree> trees, float y)
{

    // std::cout << "pppppp---" << trees[0].data[0]->x;
    std::vector<float> all_last_y_from_tree;
    // std::cout << std::endl;
    // std::cout << trees.size();
    for (int i = 0; i < trees.size(); i++)
    {
        // trees[need_x].data.push_back(new vector_2d(i, point_y / streak));

        // std::cout << "vot " << trees[i].data.back()->x << "    ";
        all_last_y_from_tree.push_back(
            trees[i].data.back().y / y);
    }
    // std::cout << std::endl;

    int need_y_position = 0;

    for (int i = 0; i < all_last_y_from_tree.size(); i++)
    {
        if (all_last_y_from_tree[i] > need_y_position)
        {
            need_y_position = i;
        }
    }
    std::cout << "POsition " << need_y_position << std::endl;

    return need_y_position;
}
std::vector<Tree> createTreePixels(std::vector<std::vector<int>> treeMatrix)
{
    std::vector<Tree> trees;
    // Tree tree;
    int x = 0;
    std::vector<float> demo_vector;
    // std::vector<int> vector_x;
    // vector_x.push_back(x);
    trees.push_back(Tree());
    trees[0].X = x;
    bool active = false;
    // trees[0].data.push_back(vector_2d(0, 0));

    int i = 0;
    for (auto vector : treeMatrix)
    {
        int streak = 0;
        float point_y = 0;
        for (int j = 0; j < vector.size(); j++)
        {
            if (vector[j] == 1)
            {
                if (demo_vector.size() == streak)
                {
                    point_y += j + 1;
                    streak += 1;
                }
                else
                {
                    // std::cout << "ttytyttyt";
                    // int need_x = defineX(trees, point_y);
                    // std::cout << "x = " << need_x << "\n";
                    // trees[need_x]
                    //     .data.push_back(vector_2d(i + 1, (float)point_y / streak));

                    // trees.push_back(Tree());
                    // x++;
                    // trees[x].X = x;
                    // point_y = 0;
                    // streak = 0;

                    // trees[x]
                    //     .data.push_back(vector_2d(i + 1, j + 1));
                }
            }
            else
            {
                streak = 0;
            }
        }
        if (streak > 0)
        {
            int need_x = defineX(trees, point_y);
            trees[need_x].data.push_back(vector_2d(i + 1, (float)point_y / streak));
            point_y = 0;
            streak = 0;
        }
        i++;
    }
    return trees;
}
// std::vector<float> new_vector;
// for (auto vector : read_matrix)
// {
//     int i = 0;
//     int streak = 0;

//     for (auto number : vector)
//     {
//         if (number == 1)
//         {
//             if (new_vector.size() == streak)
//             {
//                 new_vector.push_back(i);
//             }
//             else{

//             }
//             streak++;

//         }
//         else
//         {

//         }
//         std::cout << number << " ";
//         i++;
//     }
//     std::cout << "\n";
// }

std::vector<std::vector<int>> a = {
    {1, 1, 0, 1, 0, 0},
    {0, 1, 0, 1, 0, 0},
    {0, 0, 1, 0, 0, 0},
    {0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 1, 0},
    {0, 0, 0, 0, 0, 1},
};
// int main()
// {
//     std::vector<std::vector<int>> different_tree = DifferentTree(a, 6, 6);
//     std::vector<Tree> trees = createTreePixels(different_tree);

//     for (auto tree : trees)
//     {
//         std::cout << tree.X << "   ";
//         for (auto vec : tree.data)
//         {
//             // for (auto vec_2d)
//             std::cout << "x = " << vec.x << " y = " << vec.y << "   ";
//         }
//         std::cout << std::endl;
//     }
//     std::cout << 123123123123;
//     return 0;
// }
