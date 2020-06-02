#ifndef APPLE_GRAPHICS_VIEW_H
#define APPLE_GRAPHICS_VIEW_H

#include "views/view.h"
#include "models/apple.h"

#include <QtGui/QPainter>

#include <cassert>

class AppleGraphicsView : public View<Apple> {
public:
    explicit AppleGraphicsView(const Apple &model)
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

    void present() final {
        assert(_painter);

        int screen_x = _screen_center_shift_x + _model.get_x() * _cell_size;
        int screen_y = _screen_center_shift_y + _model.get_y() * _cell_size;
        _painter->fillRect(screen_x, screen_y, _cell_size - _cell_margin, _cell_size - _cell_margin, QBrush(QColor(255, 255, 255)));
    }

private:
    QPainter *_painter;

    int _cell_size;
    int _cell_margin;
    int _screen_center_shift_x;
    int _screen_center_shift_y;
};

#endif
