#include "console_window.h"

#include "vendor/conio.h"

#include <chrono>
#include <thread>
#include <cstdlib>

#ifdef _WIN32
enum Keys {
    KEY_UP    = 72,
    KEY_DOWN  = 80,
    KEY_LEFT  = 75,
    KEY_RIGHT = 77
};
#else
enum Keys {
    ARROWS    = '\033',
    KEY_UP    = 'A',
    KEY_DOWN  = 'B',
    KEY_LEFT  = 'D',
    KEY_RIGHT = 'C'
};
#endif

void ConsoleWindow::start()
{
    std::system("clear || cls");

    while (true) {
       _field_view.present();
       _field.step_simulation();

        if (_kbhit()) {
#ifndef _WIN32
            if (_getch() == ARROWS) {
                _getch();
#endif
                switch(_getch()) {
                    case KEY_UP:
                        _snake.turn_up();
                        break;
                    case KEY_DOWN:
                        _snake.turn_down();
                        break;
                    case KEY_LEFT:
                        _snake.turn_left();
                        break;
                    case KEY_RIGHT:
                        _snake.turn_right();
                        break;
                }
#ifndef _WIN32
            }
#endif
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(PAUSE_IN_MS));
    }
}
