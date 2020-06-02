#ifndef WINDOW_H
#define WINDOW_H

#include "models/field.h"

class Window {
public:
    Window() : _snake(_field.get_snake()) {}
    virtual ~Window() = default;

    virtual void start() = 0;

protected:
    Field _field;
    Snake &_snake;
};

#endif
