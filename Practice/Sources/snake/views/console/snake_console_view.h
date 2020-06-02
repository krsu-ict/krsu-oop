#ifndef SNAKE_CONSOLE_VIEW_H
#define SNAKE_CONSOLE_VIEW_H

#include "views/view.h"
#include "models/snake.h"

#include <iostream>

class SnakeConsoleView : public View<Snake> {
public:
    static const char SNAKE_CELL = '@';
    static const char DEAD_SNAKE_CELL = '#';

    explicit SnakeConsoleView(const Snake &model) : View(model) {}

    void present() final
    {
        std::cout << (_model.is_alive() ? SNAKE_CELL : DEAD_SNAKE_CELL);
    }
};

#endif
