#ifndef FIELD_CONSOLE_VIEW_H
#define FIELD_CONSOLE_VIEW_H

#include "views/view.h"
#include "models/field.h"

class FieldConsoleView : public View<Field> {
public:
    static const char FIELD_CELL = '.';

    explicit FieldConsoleView(const Field &model) : View(model) {}

    void present() final;
};

#endif
