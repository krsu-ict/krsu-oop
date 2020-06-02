#ifndef APPLE_H
#define APPLE_H

class Apple {
public:
    Apple() : Apple(0, 0) {}

    Apple(int x, int y) : _x(x), _y(y) {}

    [[nodiscard]] int get_x() const
    {
        return _x;
    }

    [[nodiscard]] int get_y() const
    {
        return _y;
    }

    [[nodiscard]] bool is_colliding_at(int x, int y) const {
        return _x == x && _y == y;
    }

private:
    int _x, _y;
};

#endif
