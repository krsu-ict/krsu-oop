#include "turtle.h"
#include "field.h"

// Turtle's behaviour (its services)

void Turtle::move(int steps)
{
    for (int i = 0; i < steps; ++i) {
        int next_x = x + dx;
        int next_y = y + dy;

        if (!field.are_coords_inside(next_x, next_y)) {
            break;
        }

        if (pen_down) {
            field.mark_cell(x, y);
        }

        x = next_x;
        y = next_y;
    }
}

