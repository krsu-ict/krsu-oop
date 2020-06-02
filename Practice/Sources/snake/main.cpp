#include <window/console_window.h>
#include <window/graphics_window.h>

#include <QApplication>

#include <string>

[[noreturn]] int main(int argc, char *argv[])
{
    auto use_window = std::find_if(argv, argv + argc, [&](char *arg) { return arg == std::string("-w") || arg == std::string("--window"); }) != argv + argc;

    std::unique_ptr<Window> window;
    if (use_window) {
        window = std::make_unique<GraphicsWindow>();
    } else {
        window = std::make_unique<ConsoleWindow>();
    }
    window->start();
}
