#include "graphics_window.h"

#include <QPainter>
#include <QTimer>
#include <QtWidgets/QApplication>

QtWindow::QtWindow(Field &field)
    : QWidget(), _field(field), _field_view(field)
{
    setWindowTitle("Snake");
    setFixedSize(500, 500);

    auto *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [&]() {
        _field.step_simulation();

        setWindowTitle(QString("Snake, Score: ") + QString::number(_field.get_snake().get_score()));
        update();
    });
    timer->start(PAUSE_IN_MS);
}

void QtWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);

    _field_view.set_painter(&painter);
    _field_view.set_event(event);
    _field_view.present();

    painter.end();
}

void QtWindow::keyPressEvent(QKeyEvent *event)
{
    Snake &snake = _field.get_snake();
    switch (event->key()) {
        case Qt::Key_Up:
            snake.turn_up();
            break;
        case Qt::Key_Down:
            snake.turn_down();
            break;
        case Qt::Key_Left:
            snake.turn_left();
            break;
        case Qt::Key_Right:
            snake.turn_right();
            break;
    }
}

void GraphicsWindow::start()
{
    int argc = 0; char *argv[1];
    QApplication app(argc, argv);

    _window = std::make_unique<QtWindow>(_field);
    _window->show();

    QApplication::exec();
}
