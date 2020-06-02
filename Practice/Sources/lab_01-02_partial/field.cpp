#include "field.h"
#include "turtle.h"

#include <iostream>

// Field's behaviour (its services)

Field::Field()
{
    for (int x = 0; x < WIDTH; ++x) {
        for (int y = 0; y < HEIGHT; ++y) {
            data[x][y] = EMPTY_CELL;
        }
    }
}

void Field::print(const Turtle &turtle)
{
    using namespace std;

    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            cout << (x == turtle.get_x() && y == turtle.get_y() ? TURTLE_CELL : data[x][y]);
        }
        cout << endl;
    }
    cout << endl;
}

