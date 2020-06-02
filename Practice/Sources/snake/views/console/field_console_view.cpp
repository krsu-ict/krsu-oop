#include "field_console_view.h"

#include "snake_console_view.h"
#include "apple_console_view.h"

#include "vendor/conio.h"

#include <iostream>
#include <iomanip>
#include <cstdlib>

#ifdef _WIN32
#include "windows.h"
#endif

void FieldConsoleView::present()
{
#ifdef _WIN32
    COORD pos = { 0, 0 };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
#else
    std::cout << "\033[" << 0 << ";" << 0 << "H";
#endif

    auto &snake = _model.get_snake();
    SnakeConsoleView snake_view(snake);
    auto &apple = _model.get_apple();
    AppleConsoleView apple_view(apple);

    int field_width = _model.get_width();
    int field_half_width = field_width / 2;
    int field_height = _model.get_height();
    std::cout << std::setw(field_half_width + 2) << "Snake" << std::endl
              << std::endl;
    std::cout << std::setw(field_half_width + 2) << "Score: " << snake.get_score() << std::endl
              << std::endl;

    for (int y = 0; y < field_height; ++y) {
        for (int x = 0; x < field_width; ++x) {
            if (apple.is_colliding_at(x, y)) {
                apple_view.present();
            } else if (snake.is_colliding_at(x, y)) {
                snake_view.present();
            } else {
                std::cout << FIELD_CELL;
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
