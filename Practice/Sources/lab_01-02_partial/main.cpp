#include "field.h"
#include "turtle.h"

#include <cstdlib>
#include <iostream>
#include <istream>
#include <sstream>
#include <string>

/*
    Entry point
 */

int main(int argc, char **argv)
{
    using namespace std;

    Field field;
    Turtle turtle(field);

    string input;
    while (getline(cin, input)) {
        stringstream stream(input);
        string command; stream >> command;
        // TODO: How to compare ignoring case?
        if (command == "PenUp") {
            turtle.put_pen_up();
        } else if (command == "PenDown") {
            turtle.put_pen_down();
        } else if (command == "TurnRight") {
            turtle.turn_right();
        } else if (command == "TurnLeft") {
            turtle.turn_left();
        } else if (command == "Move") {
            int steps; stream >> steps;
            turtle.move(steps);
        } else if (command == "Display") {
            field.print(turtle);
        } else if (command == "Exit") {
            exit(0);
        } else {
            cerr << "Invalid command. Try again..." << endl;
        }
    }

    return 0;
}

