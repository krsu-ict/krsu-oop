#ifndef CONSOLE_WINDOW_H
#define CONSOLE_WINDOW_H

#include "window.h"

#include "views/console/field_console_view.h"

class ConsoleWindow : public Window {
public:
    const int PAUSE_IN_MS = 33;

    ConsoleWindow() : _field_view(_field) { }

    [[noreturn]] void start() override;

private:
    FieldConsoleView _field_view;
};

#endif
