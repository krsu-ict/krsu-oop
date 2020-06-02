#pragma once

#include "shape.h"

class Rectangle : public Shape {
public:
    Rectangle(int x, int y, int width, int height)
        : Shape(x, y), _width(width), _height(height) {}

    bool contains(int x, int y) override
    {
        return x >= _x && x < _x + _width &&
               y >= _y && y < _y + _height;
    }

    void present(QPainter *painter) override
    {
        painter->setBrush(QColor(0, 0, 255));
        if (_selected) {
            painter->setPen(QPen(QColor(255, 0, 0)));
        } else {
            painter->setPen(Qt::NoPen);
        }
        painter->drawRect(_x, _y, _width, _height);
    }

private:
    int _width, _height;
};

