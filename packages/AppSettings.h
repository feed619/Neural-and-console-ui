#ifndef APP_SETTINGS_H
#define APP_SETTINGS_H

#include <string>

namespace UI
{
    std::string pixel = "  ";
    std::string fill_pixel = "██";
    std::string bot_border_pixel = "‾‾";
    std::string top_border_pixel = "__";

    std::string minus = "█─█";
    std::string board = "─";
    std::string left_board = "    ";
    std::string str_btn = "";
    std::string top_board = "\n\n\n";

    std::string clear_btn = str_btn + "|" + "clear" + "|";
    std::string start_btn = str_btn + "|" + "start" + "|";
    std::string buttons = left_board + " _____  _____" + "\n" + left_board + clear_btn + start_btn + "\n" + left_board + " ‾‾‾‾‾  ‾‾‾‾‾" + "\n";

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
}

#endif