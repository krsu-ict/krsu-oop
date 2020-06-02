#include "window.h"

#include <iostream>
#include <vector>
#include <memory>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    Window *window = new Window;
    window->show();

    QApplication::exec();

    /*
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Rectangle>(10, 10, 100, 100));
    shapes.push_back(std::make_unique<Rectangle>(50, 60, 100, 200));
    shapes.push_back(std::make_unique<Circle>(50, 60, 20));
    shapes.push_back(std::make_unique<Circle>(100, 100, 20));

    bool should_stop = false;
    while (!should_stop) {
        std::cout << "Command: ";
        std::string command; std::cin >> command;

        if (command == "stop" || command == "end") {
            should_stop = true;
        } else if (command == "present") {
            for (auto &shape : shapes) {
                shape->present();
            }
        } else if (command == "click") {
            std::cout << "mouse x: ";
            int x; std::cin >> x;
            std::cout << "mouse y: ";
            int y; std::cin >> y;

            for (auto &shape : shapes) {
                if (shape->contains(x, y)) {
                    shape->present();
                }
            }
        }
    }
    */

    return 0;
}

