#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include <functional>

class Field;
class Apple;

class Snake {
public:
    static const int UPDATE_RATE = 3;

    Snake() : Snake(0, 0, 1, 0) {}

    Snake(int x, int y, int dx, int dy);

    [[nodiscard]] bool is_alive() const
    {
        return _alive;
    }

    [[nodiscard]] int get_score() const
    {
        return _score;
    }
    
    [[nodiscard]] int get_length() const
    {
        return _length;
    }

    [[nodiscard]] const std::vector<int> &get_x() const
    {
        return _x;
    }

    [[nodiscard]] const std::vector<int> &get_y() const
    {
        return _y;
    }

    [[nodiscard]] bool is_colliding_at(int x, int y) const;

    void turn_up()
    {
        if (_dy != 1) {
            _dx = 0;
            _dy = -1;
        }
    }

    void turn_down()
    {
        if (_dy != -1) {
            _dx = 0;
            _dy = 1;
        }
    }

    void turn_left()
    {
        if (_dx != 1) {
            _dx = -1;
            _dy = 0;
        }
    }

    void turn_right()
    {
        if (_dx != -1) {
            _dx = 1;
            _dy = 0;
        }
    }

    void move(Field *field, const std::function<void(void)>& on_collided_with_apple);

private:
    std::vector<int> _x, _y;
    int _dx, _dy;
    int _head;
    int _length;
    bool _alive;
    int _score;
    int _move_request;
};

#endif
