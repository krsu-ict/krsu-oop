#include "rational.h"

#include <sstream>
#include <stdexcept>

Rational::Rational(int numerator, int denominator)
    : _numerator(numerator), _denominator(denominator)
{
    _init();
}

Rational::Rational(const std::string &line)
{
    _init_from_string(line);
}

void Rational::_init_from_string(const std::string &line)
{
    std::stringstream stream(line);

    char slash;
    int numerator, denominator;
    if ((stream >> numerator >> slash >> denominator) && slash == '/') {
        _numerator = numerator;
        _denominator = denominator;
        _init();
    } else {
        std::stringstream stream(line);
        if (stream >> numerator) {
            _numerator = numerator;
            _denominator = 1;
            _init();
        } else {
            throw std::invalid_argument("Неверное рациональное число: " + line);
        }
    }
}

void Rational::_init()
{
    if (_denominator == 0) {
        throw std::invalid_argument("Неверное рациональное число: знаменатель не может быть равен нулю");
    }

    if (_denominator < 0) {
        _numerator = -_numerator;
        _denominator = -_denominator;
    }

    _simplify();
}

int Rational::_gcd(int a, int b)
{
    return b == 0 ? a : _gcd(b, a % b);
}

void Rational::_simplify()
{
    int gcd = _gcd(_numerator, _denominator);
    _numerator /= gcd;
    _denominator /= gcd;
}

Rational& Rational::operator+=(const Rational &other)
{
    _numerator = _numerator * other._denominator + _denominator * other._numerator;
    _denominator = _denominator * other._denominator;

    _simplify();

    return *this;
}

Rational& Rational::operator-=(const Rational &other)
{
    _numerator = _numerator * other._denominator - _denominator * other._numerator;
    _denominator = _denominator * other._denominator;

    _simplify();

    return *this;
}

Rational& Rational::operator*=(const Rational &other)
{
    _numerator = _numerator * other._numerator;
    _denominator = _denominator * other._denominator;

    _simplify();

    return *this;
}

Rational& Rational::operator/=(const Rational &other)
{
    _numerator = _numerator * other._denominator;
    _denominator = _denominator * other._numerator;

    _simplify();

    return *this;
}

Rational operator+(Rational left, const Rational &right)
{
    return left += right;
}

Rational operator-(Rational left, const Rational &right)
{
    return left -= right;
}

Rational operator*(Rational left, const Rational &right)
{
    return left *= right;
}

Rational operator/(Rational left, const Rational &right)
{
    return left /= right;
}

bool Rational::operator==(const Rational &other) const
{
    return (*this - other)._numerator == 0;
}

bool Rational::operator!=(const Rational &other) const
{
    return !(*this == other);
}

bool Rational::operator<(const Rational &other) const
{
    return (*this - other)._numerator < 0;
}

bool Rational::operator>(const Rational &other) const
{
    return (other < *this);
}

bool Rational::operator<=(const Rational &other) const
{
    return !(*this > other);
}

bool Rational::operator>=(const Rational &other) const
{
    return !(*this < other);
}

std::ostream& operator<<(std::ostream &out, const Rational &rational)
{
    out << rational.get_numerator();
    if (rational.get_denominator() != 1) {
        out << '/' << rational.get_denominator();
    }

    return out;
}

std::istream& operator>>(std::istream &in, Rational &rational)
{
    std::string line;
    std::getline(in, line);
    rational._init_from_string(line);

    return in;
}

Rational::operator std::string() const
{
    std::string result = std::to_string(_numerator);
    if (_denominator != 1) {
        result += '/';
        result += std::to_string(_denominator);
    }

    return result;
}

