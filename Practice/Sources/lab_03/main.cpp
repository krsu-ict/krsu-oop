#include "rational.h"

#include <iostream>
#include <stdexcept>
#include <string>

int main(int argc, char **argv)
{
    using namespace std;

    cout << "Калькулятор рациональных чисел" << endl
         << "==============================" << endl;

    while (true) {
        cout << "Введите первое число (Ctrl-Z/Ctrl+D: для выхода): ";
        string firstInput; cin >> firstInput; if (cin.eof()) { break; }
        Rational first;
        try {
            first = firstInput;
        } catch (const invalid_argument &e) {
            cout << e.what() << endl;
            continue;
        }

        cout << "Введите оператор: ";
        string op; cin >> op; if (cin.eof()) { break; }
        if (!(op == "+"  || op == "-" || op == "*"  || op == "/" ||
              op == "<"  || op == ">" || op == "<=" || op == ">=" ||
              op == "==" || op == "!=")) {
              cout << "Неверный оператор" << endl;
              continue;
        }

        cout << "Введите второе число (Ctrl-Z/Ctrl+D: для выхода): ";
        string secondInput; cin >> secondInput; if (cin.eof()) { break; }
        Rational second;
        try {
            second = secondInput;
        } catch (const invalid_argument &e) {
            cout << e.what() << endl;
            continue;
        }

        string result;
        if (op == "+") {
            result = (string) (first + second);
        } else if (op == "-") {
            result = (string) (first - second);
        } else if (op == "*") {
            result = (string) (first * second);
        } else if (op == "/") {
            result = (string) (first / second);
        } else if (op == "<") {
            result = first < second ? "верно" : "не верно";
        } else if (op == ">") {
            result = first > second ? "верно" : "не верно";
        } else if (op == "<=") {
            result = first <= second ? "верно" : "не верно";
        } else if (op == ">=") {
            result = first >= second ? "верно" : "не верно";
        } else if (op == "==") {
            result = first == second ? "верно" : "не верно";
        } else if (op == "!=") {
            result = first != second ? "верно" : "не верно";
        }
        cout << "Результат: " << first << " " << op << " " << second << " = " << result << endl;
    }

    return 0;
}

