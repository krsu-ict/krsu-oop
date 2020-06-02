#include "field.h"

void Field::place_new_apple()
{
    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<> random_width(0, _width - 1);
    std::uniform_int_distribution<> random_height(0, _height - 1);

    int x, y;
    do {
        x = random_width(generator);
        y = random_height(generator);
    } while(_snake.is_colliding_at(x, y));

    _apple = Apple(x, y);
}

void Field::step_simulation()
{
    const auto on_collided_with_apple = [&]() {
        place_new_apple();
    };

    _snake.move(this, on_collided_with_apple);
}
