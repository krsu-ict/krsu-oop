#ifndef APPLE_CONSOLE_VIEW_H
#define APPLE_CONSOLE_VIEW_H

#include "views/view.h"
#include "models/apple.h"

#include <iostream>

class AppleConsoleView : public View<Apple> {
public:
    static const char APPLE_CELL = '*';

    explicit AppleConsoleView(const Apple &model) : View(model) {}

    void present() final
    {
        std::cout << APPLE_CELL;
    }
};

#endif
