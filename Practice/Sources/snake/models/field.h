#ifndef FIELD_H
#define FIELD_H

#include "snake.h"
#include "apple.h"

#include <random>

class Field {
public:
    static const int DEFAULT_FIELD_WIDTH = 20;
    static const int DEFAULT_FIELD_HEIGHT = 20;

    Field() : Field(DEFAULT_FIELD_WIDTH, DEFAULT_FIELD_HEIGHT) {}

    Field(int width, int height) : _width(width), _height(height)
    {
        place_new_apple();
    }

    [[nodiscard]] int get_width() const
    {
        return _width;
    }

    [[nodiscard]] int get_height() const
    {
        return _height;
    }

    [[nodiscard]] const Snake &get_snake() const
    {
        return _snake;
    }

    [[nodiscard]] const Apple &get_apple() const
    {
        return _apple;
    }

    [[nodiscard]] Snake &get_snake()
    {
        return _snake;
    }

    [[nodiscard]] Apple &get_apple()
    {
        return _apple;
    }

    [[nodiscard]] bool are_coords_inside(int x, int y) const
    {
        return x >= 0 && x < _width &&
               y >= 0 && y < _height;
    }

    void place_new_apple();

    void step_simulation();

private:
    int _width, _height;

    Snake _snake;
    Apple _apple;
};

#endif
