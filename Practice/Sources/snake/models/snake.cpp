#include "snake.h"

#include "field.h"

Snake::Snake(int x, int y, int dx, int dy)
    : _dx(dx), _dy(dy), _head(0), _length(3), _alive(true), _score(0), _move_request(0)
{
    for (int i = 0; i < _length; ++i) {
        _x.push_back(x);
        _y.push_back(y);
    }
}

bool Snake::is_colliding_at(int x, int y) const
{
    for (int i = 0; i < _length; ++i) {
        if (_x[i] == x && _y[i] == y) {
            return true;
        }
    }

    return false;
}

void Snake::move(Field *field, const std::function<void(void)> &on_collided_with_apple)
{
    if (_move_request++ % UPDATE_RATE != 0 || !_alive) {
        return;
    }

    int next_x = _x[_head] + _dx;
    int next_y = _y[_head] + _dy;
    if (!field->are_coords_inside(next_x, next_y) || is_colliding_at(next_x, next_y)) {
        _alive = false;
    } else {
        if (field->get_apple().is_colliding_at(next_x, next_y)) {
            int nextX = _x[_head];
            int nextY = _y[_head];

            _x.insert(std::begin(_x) + _head, nextX);
            _y.insert(std::begin(_y) + _head, nextY);

            ++_length;
            ++_score;

            on_collided_with_apple();
        } else {
            _head = (_head + 1) % _length;
            _x[_head] = next_x;
            _y[_head] = next_y;
        }
    }
}
