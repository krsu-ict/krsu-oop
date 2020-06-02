#include "field_graphics_view.h"

#include <cassert>

void FieldGraphicsView::present()
{
    assert(_painter);
    assert(_event);

    auto &snake = _model.get_snake();
    auto &apple = _model.get_apple();

    int field_width = _model.get_width();
    int field_height = _model.get_height();
    int screen_width = _event->rect().width();
    int screen_height = _event->rect().height();
    int cell_size = static_cast<int>(fmin(screen_width / field_width, screen_height / field_height));
    int cell_margin = 1;
    int field_screen_width = cell_size * field_width;
    int field_screen_height = cell_size * field_height;
    int screen_center_shift_x = (screen_width - field_screen_width) / 2;
    int screen_center_shift_y = (screen_height - field_screen_height) / 2;

    _painter->fillRect(_event->rect(), QBrush(QColor(0, 0, 0)));
    for (int y = 0; y < field_height; ++y) {
        for (int x = 0; x < field_width; ++x) {
            int screen_x = screen_center_shift_x + x * cell_size;
            int screen_y = screen_center_shift_y + y * cell_size;
            _painter->fillRect(screen_x, screen_y, cell_size - cell_margin, cell_size - cell_margin, QBrush(QColor(64, 64, 64)));
        }
    }

    AppleGraphicsView apple_view(apple);
    apple_view.set_painter(_painter);
    apple_view.set_cell_size(cell_size);
    apple_view.set_cell_margin(cell_margin);
    apple_view.set_screen_center_shift_x(screen_center_shift_x);
    apple_view.set_screen_center_shift_y(screen_center_shift_y);
    apple_view.present();

    SnakeGraphicsView snake_view(snake);
    snake_view.set_painter(_painter);
    snake_view.set_cell_size(cell_size);
    snake_view.set_cell_margin(cell_margin);
    snake_view.set_screen_center_shift_x(screen_center_shift_x);
    snake_view.set_screen_center_shift_y(screen_center_shift_y);
    snake_view.present();
}
