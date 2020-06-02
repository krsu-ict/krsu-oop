#ifndef GRAPHICS_WINDOW_H
#define GRAPHICS_WINDOW_H

#include "window.h"

#include "models/field.h"
#include "views/graphics/field_graphics_view.h"

#include <QtWidgets/QWidget>

#include <memory>

class QtWindow : public QWidget {
Q_OBJECT

public:
    const int PAUSE_IN_MS = 33;

    explicit QtWindow(Field &field);

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    Field &_field;
    FieldGraphicsView _field_view;
};

class GraphicsWindow : public Window {
public:
    GraphicsWindow(): _window(nullptr) {}

    void start() final;

private:
    std::unique_ptr<QtWindow> _window;
};

#endif
