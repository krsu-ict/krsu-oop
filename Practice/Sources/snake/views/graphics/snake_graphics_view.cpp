#include "snake_graphics_view.h"

#include <cassert>

void SnakeGraphicsView::present()
{
    assert(_painter);

    for (int i = 0; i < _model.get_length(); ++i) {
        int screen_x = _screen_center_shift_x + _model.get_x()[i] * _cell_size;
        int screen_y = _screen_center_shift_y + _model.get_y()[i] * _cell_size;
        QBrush brush = _model.is_alive() ? QBrush(QColor(255, 0, 0)) : QBrush(QColor(200, 200, 200));
        _painter->fillRect(screen_x, screen_y, _cell_size - _cell_margin, _cell_size - _cell_margin, brush);
    }
}
