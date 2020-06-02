#ifndef SNAKE_GRAPHICS_VIEW_H
#define SNAKE_GRAPHICS_VIEW_H

#include "views/view.h"
#include "models/snake.h"

#include <QtGui/QPainter>

class SnakeGraphicsView : public View<Snake> {
public:
    explicit SnakeGraphicsView(const Snake &model)
        : View(model),
          _painter(nullptr),
          _cell_size(-1), _cell_margin(-1),
          _screen_center_shift_x(-1), _screen_center_shift_y(-1) { }

    void set_painter(QPainter *painter)
    {
        _painter = painter;
    }

    void set_cell_size(int cell_size)
    {
        _cell_size = cell_size;
    }

    void set_cell_margin(int cell_margin)
    {
        _cell_margin = cell_margin;
    }

    void set_screen_center_shift_x(int screen_center_shift_x)
    {
        _screen_center_shift_x = screen_center_shift_x;
    }

    void set_screen_center_shift_y(int screen_center_shift_y)
    {
        _screen_center_shift_y = screen_center_shift_y;
    }

    void present() final;

private:
    QPainter *_painter;

    int _cell_size;
    int _cell_margin;
    int _screen_center_shift_x;
    int _screen_center_shift_y;
};

#endif
