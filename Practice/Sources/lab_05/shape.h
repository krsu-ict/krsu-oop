#pragma once

#include <QPainter>

class Shape {
public:
    Shape(int x, int y): _x(x), _y(y), _selected(false) {}
    virtual ~Shape() {}

    virtual bool contains(int x, int y) = 0;

    virtual void present(QPainter *painter) = 0;

    void set_selected(bool selected)
    {
        _selected = selected;
    }

    void move(int dx, int dy)
    {
        _x += dx;
        _y += dy;
    }

protected:
    int _x, _y;
    bool _selected;
};

