#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include "windows.h"
#include <cmath>

#include "packages/functions.cpp"
#include "packages/AppSettings.h"
#include "packages/neural.cpp"
using namespace UI;

std::vector<std::vector<int>> matrix_holst;
std::vector<std::vector<double>> matrix_weight_layer;
int MATRIX_SIZE = 28;
// 1 символ 19 пиксель в высоту
// 1 символ 19 пиксель в ширину

// высота конец 68 начало 448
// ширина начало 308 конец 688

void create_matrix_holst(std::vector<std::vector<int>> &matrix_holst)
{
    for (int i = 0; i < height; i++)
    {
        std::vector<int> demo_vector;
        for (int j = 0; j < width; j++)
        {
            demo_vector.push_back(0);
        }
        matrix_holst.push_back(demo_vector);
    }
}

std::string mtp_strin_on_number(std::string char_, int count)
{

    std::string new_strin = "";
    for (int i = 0; i < count; i++)
    {
        new_strin += char_;
    }
    return new_strin;
}
void print_holst_and_matrix(std::vector<std::vector<int>> &matrix_holst)
{
    std::string string_holst = top_board;
    std::string string_matrix_holst = "";

    int i = 0;
    for (auto vector_i : matrix_holst)
    {
        string_holst += left_board;
        string_matrix_holst = "";
        string_matrix_holst += left_board;

        for (int number : vector_i)
        {
            if (number == 0)
            {
                string_holst += pixel;
            }
            else
            {
                string_holst += fill_pixel;
            }
            string_matrix_holst = string_matrix_holst + std::to_string(number) + " ";
        }
        string_holst = string_holst + "|" + string_matrix_holst + "\n";
        string_matrix_holst += "\n";
        i++;
    }
    string_holst += bot_border;
    std::cout << string_holst + buttons + top_board + '\0';
}

bool check_holst(std::vector<std::vector<int>> &matrix_holst, POINT &cursorPos)
{
    HWND consoleWindow = GetConsoleWindow();

    ScreenToClient(consoleWindow, &cursorPos);
    bool change = false;
    if ((cursorPos.x >= start_holst_x && cursorPos.x <= end_holst_x))
    {
        if ((cursorPos.y >= start_holst_y && cursorPos.y <= end_holst_y))
        {
            int pixel_x = std::round((cursorPos.x - start_holst_x) / (float)width_pixle_x);
            int pixel_y = std::round((cursorPos.y - start_holst_y) / (float)height_pixle_y);
            if (matrix_holst[pixel_y][pixel_x] == 0)
            {
                matrix_holst[pixel_y][pixel_x] = 1;
                change = true;
            }
        }
        else if ((cursorPos.y >= end_holst_y + 1 * height_pixle_y) && (cursorPos.y <= end_holst_y + 4 * height_pixle_y))
        {

            if ((cursorPos.x <= start_holst_x + width_btn_x * width_pixle_x))
            {
                ClearMatrix(matrix_holst, width, height);
            }
            else if ((cursorPos.x <= start_holst_x + width_btn_x * 2 * width_pixle_x))
            {
                std::cout << GetResult(matrix_weight_layer, matrix_holst) << "\n";
                system("pause");
            }
            else if ((cursorPos.x <= start_holst_x + width_btn_x * 3 * width_pixle_x))
            {
                std::cout << "Обученна\n";
                Traning(matrix_weight_layer, matrix_holst, 1);
                SaveWeights(matrix_weight_layer, "weight_layer");
                system("pause");
            }
            else if ((cursorPos.x <= start_holst_x + width_btn_x * 4 * width_pixle_x))
            {
                std::cout << "Обученна\n";
                Traning(matrix_weight_layer, matrix_holst, 0);
                SaveWeights(matrix_weight_layer, "weight_layer");
                system("pause");
            }
        }
    }
    return change;
}
void Start()
{
    int i = 0;
    bool active_click = false;

    while (true)
    {
        if (GetAsyncKeyState(VK_RBUTTON))
        {
            POINT cursorPos;
            GetCursorPos(&cursorPos);
            if ((cursorPos.x > end_holst_x) or cursorPos.y > end_holst_y + end_buttons_y)
            {
                continue;
            }
            active_click = true;
            check_holst(matrix_holst, cursorPos);
            if (i >= 10)
            {
                i = 0;
                system("cls");
                print_holst_and_matrix(matrix_holst);
            }
            i++;
        }
        else
        {
            if (active_click)
            {
                active_click = false;
                system("cls");
                print_holst_and_matrix(matrix_holst);
            }
        }
        Sleep(1);
    }
}
int main()
{
    matrix_weight_layer = LoadWeights("weight_layer");
    if (matrix_weight_layer.size() == 0)
        matrix_weight_layer = CreateWeightLayer(2, MATRIX_SIZE * MATRIX_SIZE);

    bot_border = left_board + mtp_strin_on_number(bot_border_pixel, width);
    top_border = left_board + mtp_strin_on_number(top_border_pixel, width);

    create_matrix_holst(matrix_holst);
    print_holst_and_matrix(matrix_holst);
    Start();
    system("pause");

    return 0;
}
