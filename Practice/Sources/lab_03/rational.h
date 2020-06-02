#ifndef RATIONAL_H
#define RATIONAL_H

#include <iostream>
#include <string>

class Rational {
public:
    Rational(): _numerator(1), _denominator(1) { }
    Rational(int numerator, int denominator = 1);
    Rational(const std::string &line);

    Rational& operator+=(const Rational &other);
    Rational& operator-=(const Rational &other);
    Rational& operator*=(const Rational &other);
    Rational& operator/=(const Rational &other);
    bool operator==(const Rational &other) const;
    bool operator!=(const Rational &other) const;
    bool operator<(const Rational &other) const;
    bool operator>(const Rational &other) const;
    bool operator<=(const Rational &other) const;
    bool operator>=(const Rational &other) const;
    operator std::string() const;

    int get_numerator() const
    {
        return _numerator;
    }

    int get_denominator() const
    {
        return _denominator;
    }

    friend std::istream& operator>>(std::istream &in, Rational &rational);

private:
    void _init_from_string(const std::string &line);
    void _init();
    static int _gcd(int a, int b);
    void _simplify();

    int _numerator;
    int _denominator;
};

Rational operator+(Rational left, const Rational &right);
Rational operator-(Rational left, const Rational &right);
Rational operator*(Rational left, const Rational &right);
Rational operator/(Rational left, const Rational &right);
std::ostream& operator<<(std::ostream &out, const Rational &rational);
std::istream& operator>>(std::istream &in, Rational &rational);

#endif

