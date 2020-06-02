#ifndef FIELD_H
#define FIELD_H

class Turtle;

class Field
{
public:
    // Field's behaviour (its services)

    Field();

    bool are_coords_inside(int x, int y)
    {
        return x >= 0 && x < WIDTH &&
               y >= 0 && y < HEIGHT;
    }

    void mark_cell(int x, int y)
    {
        data[x][y] = MARKED_CELL;
    }

    void print(const Turtle &turtle);

private:
    // Field's data (its state)

    static const char EMPTY_CELL  = '.';
    static const char MARKED_CELL = '*';
    static const char TURTLE_CELL = 'T';

    static const int WIDTH  = 20;
    static const int HEIGHT = 20;

    char data[WIDTH][HEIGHT];
};

#endif

