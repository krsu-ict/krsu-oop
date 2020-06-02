#pragma once

#include "shape.h"

class Circle : public Shape {
public:
    Circle(int x, int y, int radius)
        : Shape(x, y), _radius(radius) {}

    bool contains(int x, int y) override
    {
        int dx = _x - x;
        int dy = _y - y;

        return dx * dx + dy * dy < _radius * _radius;
    }

    void present(QPainter *painter) override
    {
        painter->setBrush(QColor(0, 0, 255));
        if (_selected) {
            painter->setPen(QPen(QColor(255, 0, 0)));
        } else {
            painter->setPen(Qt::NoPen);
        }
        painter->drawEllipse(_x - _radius, _y - _radius, _radius * 2, _radius * 2);
    }

private:
    int _radius;
};

