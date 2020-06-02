#ifndef FIELD_GRAPHICS_VIEW_H
#define FIELD_GRAPHICS_VIEW_H

#include "views/view.h"
#include "models/field.h"

#include "snake_graphics_view.h"
#include "apple_graphics_view.h"

#include <QtGui/QPainter>
#include <QtGui/QPaintEvent>

#include <cmath>

class FieldGraphicsView : public View<Field> {
public:
    explicit FieldGraphicsView(const Field &model)
        : View(model), _painter(nullptr), _event(nullptr) { }

    void set_painter(QPainter *painter)
    {
        _painter = painter;
    }

    void set_event(QPaintEvent *event)
    {
        _event = event;
    }

    void present() final;

private:
    QPainter *_painter;
    QPaintEvent *_event;
};

#endif
