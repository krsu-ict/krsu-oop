#ifndef TURTLE_H
#define TURTLE_H

class Field;

class Turtle
{
public:
    // Turtle's behaviour (its services)

    Turtle(Field &field) : x(0), y(0), dx(1), dy(0), pen_down(false), field(field) { }

    int get_x() const
    {
        return x;
    }

    int get_y() const
    {
        return y;
    }

    void put_pen_up()
    {
        pen_down = false;
    }

    void put_pen_down()
    {
        pen_down = true;
    }

    void turn_right()
    {
        int temp = dx;
        dx = -dy;
        dy = temp;
    }

    void turn_left()
    {
        int temp = dx;
        dx = dy;
        dy = -temp;
    }

    void move(int steps);

private:
    // Turtle's data (its state)

    int x, y;
    int dx, dy;
    bool pen_down;
    Field &field;
};

#endif

