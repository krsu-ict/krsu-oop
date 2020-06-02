#include "stack.h"

#include <iostream>

struct Point {
    int x, y;
};

int main(int argc, char **argv)
{
    // Пример использования класса

    Stack<Point> stack1;
    stack1.push(Point{1, 2});
    stack1.push(Point{3, 4});
    stack1.push(Point{7, 5});

    while (!stack1.is_empty()) {
        std::cout << stack1.top().x << ", " << stack1.top().y << std::endl;
        stack1.pop();
    }
    std::cout << std::endl;

    Stack<int> stack2;
    stack2.push(1);
    stack2.push(2);
    stack2.push(3);

    while (!stack2.is_empty()) {
        std::cout << stack2.top() << std::endl;
        stack2.pop();
    }

    return 0;
}

