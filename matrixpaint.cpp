#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include "windows.h"
#include <cmath>

#include "packages/functions.cpp"

// std::string pixel = "░░";
std::string pixel = "  ";
// std::string pixel = "██";
// std::string pixel = "__";
// std::string pixel = "¶¶";
std::string fill_pixel = "██";
std::string bot_border_pixel = "‾‾";
std::string top_border_pixel = "__";
// std::string fill_pixel = "¶¶";

std::string minus = "█─█";
std::string board = "─";
// std::string left_board = "\t";
std::string left_board = "    ";
std::string str_btn = "";
std::string top_board = "\n\n\n";

std::string clear_btn = str_btn + "|" + "clear" + "|";
std::string start_btn = str_btn + "|" + "start" + "|";
std::string buttons = left_board + " _____  _____" + "\n" + left_board + clear_btn + start_btn + "\n" + left_board + " ‾‾‾‾‾  ‾‾‾‾‾" + "\n";

// std::string clear_btn = str_btn + " _____"  left_board + "|" + "clear" + "|" + "\n" + left_board + " ‾‾‾‾‾";
// std::string start_btn = str_btn + " _____" + "\n" + left_board + "|" + "start" + "|" + "\n" + left_board + " ‾‾‾‾‾";
// std::string buttons = left_board + clear_btn + start_btn + "\n";
std::vector<std::vector<int>> matrix_holst;

int width = 28;
int height = 28;
int width_pixle_x = 16;
int width_pixle_y = 16;

int start_holst_x = 40;
int end_holst_x = start_holst_x + width_pixle_x * width;

int start_holst_y = 72;
int end_holst_y = start_holst_y + width_pixle_x * height;

std::string bot_border = "";
std::string top_border = "";
// 1 символ 19 пиксель в высоту
// 1 символ 19 пиксель в ширину

// высота конец 68 начало 448
// ширина начало 308 конец 688

void create_matrix_holst(std::vector<std::vector<int>> &matrix_holst)
{
    for (int i = 0; i < height; i++)
    {
        std::vector<int> demo_vector;
        // std::cout << left_board+'\0';
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

    // std::cout << string_holst + string_matrix_holst + '\0';
    std::cout << string_holst + "\n" + buttons + top_board + '\0';
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
            int pixel_y = std::round((cursorPos.y - start_holst_y) / (float)width_pixle_y);
            // int pixel_x = int((cursorPos.x - start_holst_x) / (float)width_pixle_x);
            // int pixel_y = int((cursorPos.y - start_holst_y) / (float)width_pixle_y);
            if (matrix_holst[pixel_y][pixel_x] == 0)
            {
                matrix_holst[pixel_y][pixel_x] = 1;
                change = true;
            }
        }
        else if ((cursorPos.y >= end_holst_y + 1 * width_pixle_y) && (cursorPos.y <= end_holst_y + 4 * width_pixle_y))
        {
            if ((cursorPos.x <= start_holst_x + 3 * width_pixle_x))
            {
                ClearMatrix(matrix_holst, width, height);
                // std::cout << "11111111111111111111111\n";
            }
            else if ((cursorPos.x <= start_holst_x + 6 * width_pixle_x))
            {
                NoiseRemoval(matrix_holst, width, height);
                // isX(matrix_holst, width, height);
            }
            // matrix_holst[1][1] = 1;
        }
    }
    return change;
}

int main()
{
    bot_border = left_board + mtp_strin_on_number(bot_border_pixel, width);
    top_border = left_board + mtp_strin_on_number(top_border_pixel, width);

    create_matrix_holst(matrix_holst);
    // HWND consoleWindow = GetConsoleWindow();
    // HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // POINT cursorPos;
    // CONSOLE_SCREEN_BUFFER_INFO csbi;
    // HWND consoleWindow = GetConsoleWindow();
    // HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // POINT cursorPos;
    // CONSOLE_SCREEN_BUFFER_INFO csbi;
    // HWND consoleWindow = GetConsoleWindow(); // Получаем HWND консоли
    // POINT cursorPos;
    print_holst_and_matrix(matrix_holst);
    // std::cout << minus;
    int i = 0;
    bool active_click = false;
    while (true)
    {

        // for (int y = 0; y < 100; ++y)
        // {
        // std::cout << pixel << "-" << y << "\n";
        // }
        // break;

        // system("cls");
        if (GetAsyncKeyState(VK_RBUTTON))
        {
            POINT cursorPos;
            GetCursorPos(&cursorPos);
            if ((cursorPos.x > end_holst_x) or cursorPos.y > end_holst_y)
            {
                continue;
            }
            active_click = true;
            // std::cout << minus;
            check_holst(matrix_holst, cursorPos);
            if (i >= 10)
            // if (check_holst(matrix_holst))
            {
                i = 0;
                system("cls");
                print_holst_and_matrix(matrix_holst);
            }
            // system("pause");
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
        // HWND consoleWindow = GetConsoleWindow();
        // POINT cursorPos;
        // GetCursorPos(&cursorPos);
        // ScreenToClient(consoleWindow, &cursorPos);
        // print_holst_and_matrix(matrix_holst);

        // int pixel_x = std::round((cursorPos.x - start_holst_x) / (float)width_pixle_x);
        // int pixel_y = std::round((cursorPos.y - start_holst_y) / (float)width_pixle_y);
        // std::cout << "Позиция мыши в консоли: X=" << cursorPos.x << " Y=" << cursorPos.y << "  " << pixel_x << "  " << pixel_y;
        // Sleep(100);
    }

    system("pause");
    return 0;
}
