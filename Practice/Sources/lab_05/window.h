#pragma once

#include "shape.h"
#include "rectangle.h"
#include "circle.h"

#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>

class Canvas : public QWidget {
Q_OBJECT

public:
    enum ShapeType {
        RectangleType,
        CircleType
    };

    Canvas(QWidget *parent):
        QWidget(parent),
        _next_shape_to_draw(RectangleType), _selected_shape(nullptr),
        _drag_enabled(false), _prev_mouse_x(0), _prev_mouse_y(0) {}

    void set_next_shape_to_draw(ShapeType type)
    {
        _next_shape_to_draw = type;
    }

protected:
    void paintEvent(QPaintEvent *event) override
    {
        QPainter painter;
        painter.begin(this);

        for (auto &shape : _shapes) {
            shape->present(&painter);
        }

        painter.end();
    }

    void mousePressEvent(QMouseEvent *event) override
    {
        if (_selected_shape != nullptr) {
            _selected_shape->set_selected(false);
            _selected_shape = nullptr;
        }

        if (event->button() == Qt::LeftButton) {
            if (_next_shape_to_draw == RectangleType) {
                _shapes.push_back(std::make_shared<Rectangle>(event->x(), event->y(), 50, 50));
                update();
            } else if (_next_shape_to_draw == CircleType) {
                _shapes.push_back(std::make_shared<Circle>(event->x(), event->y(), 25));
                update();
            }
        } else if (event->button() == Qt::RightButton) {
            for (auto &shape : _shapes) {
                if (shape->contains(event->x(), event->y())) {
                    shape->set_selected(true);
                    _selected_shape = shape;

                    _prev_mouse_x = event->x();
                    _prev_mouse_y = event->y();
                    _drag_enabled = true;

                    update();
                    break;
                }
            }
        }
    }

    void mouseMoveEvent(QMouseEvent *event) override
    {
        if (_drag_enabled && _selected_shape != nullptr) {
            _selected_shape->move(event->x() - _prev_mouse_x, event->y() - _prev_mouse_y);
            _prev_mouse_x = event->x();
            _prev_mouse_y = event->y();

            update();
        }
    }

    void mouseReleaseEvent(QMouseEvent *event) override
    {
        _drag_enabled = false;
    }

private:
    ShapeType _next_shape_to_draw;

    std::vector<std::shared_ptr<Shape>> _shapes;
    std::shared_ptr<Shape> _selected_shape;

    bool _drag_enabled;
    int _prev_mouse_x;
    int _prev_mouse_y;
};

class Window : public QWidget {
Q_OBJECT

public:
    Window() : QWidget()
    {
        setWindowTitle("Graphics Editor");
        setFixedSize(500, 500);

        auto *layout = new QGridLayout(this);
        setLayout(layout);

        _canvas = new Canvas(this);
        layout->addWidget(_canvas, 0, 0, 1, 2);

        _rectangle_button = new QPushButton("Rectangle", this);
        _rectangle_button->setStyleSheet("background-color: red; color: white;");
        connect(_rectangle_button, &QPushButton::clicked, [&]() {
            _rectangle_button->setStyleSheet("background-color: red; color: white;");
            _circle_button->setStyleSheet("background-color: white; color: black;");
            _canvas->set_next_shape_to_draw(Canvas::ShapeType::RectangleType);
        });
        layout->addWidget(_rectangle_button, 1, 0);

        _circle_button = new QPushButton("Circle", this);
        _circle_button->setStyleSheet("background-color: white; color: black;");
        connect(_circle_button, &QPushButton::clicked, [&]() {
            _rectangle_button->setStyleSheet("background-color: white; color: black;");
            _circle_button->setStyleSheet("background-color: red; color: white;");
            _canvas->set_next_shape_to_draw(Canvas::ShapeType::CircleType);
        });
        layout->addWidget(_circle_button, 1, 1);
        layout->setMargin(0);
    }

private:
    Canvas *_canvas;
    QPushButton *_rectangle_button;
    QPushButton *_circle_button;
};

