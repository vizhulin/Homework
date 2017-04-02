#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <cstring>

using namespace std;


class RationalDivisionByZero : logic_error {
public:
    RationalDivisionByZero();
};

RationalDivisionByZero::RationalDivisionByZero() : logic_error("Division by zero") {}

class Rational {
private:
    int numerator;
    int denominator;

    void assign(const char *);

    int nod() {
        int a = abs(numerator);
        int b = abs(denominator);
        while (b) {
            a = a % b;
            swap(a, b);
        }
        return a;
    };

    void reduce() {
        int sign = 1;
        if (numerator * denominator < 0)
            sign = -1;
        int a = nod();
        numerator = abs(numerator) / a * sign;
        denominator /= a;
    }

public:
    Rational();

    Rational(const int &, const int & = 1);

    Rational(const Rational &);

    int getNumerator() const;

    int getDenominator() const;

    friend istream &operator>>(istream &, Rational &);

    friend ostream &operator<<(ostream &, const Rational &);

    friend Rational operator+(const Rational &, const Rational &);

    friend Rational operator+(const Rational &, const int &);

    friend Rational operator+(const int &, const Rational &);

    friend Rational operator-(const Rational &, const Rational &);

    friend Rational operator-(const Rational &, const int &);

    friend Rational operator-(const int &, const Rational &);

    friend Rational operator*(const Rational &, const Rational &);

    friend Rational operator*(const Rational &, const int &);

    friend Rational operator*(const int &, const Rational &);

    friend Rational operator/(const Rational &, const Rational &);

    friend Rational operator/(const Rational &, const int &);

    friend Rational operator/(const int &, const Rational &);

    friend Rational operator-(const Rational &);

    friend Rational operator+(const Rational &);

    Rational &operator=(const Rational &);

    Rational &operator=(const int &);

    Rational &operator+=(const Rational &);

    Rational &operator+=(const int &);

    Rational &operator-=(const Rational &);

    Rational &operator-=(const int &);

    Rational &operator*=(const Rational &);

    Rational &operator*=(const int &);

    Rational &operator/=(const Rational &);

    Rational &operator/=(const int &);

    friend bool operator==(const Rational &, const Rational &);

    friend bool operator==(const Rational &, const int &);

    friend bool operator==(const int &, const Rational &);

    friend bool operator!=(const Rational &, const Rational &);

    friend bool operator!=(const Rational &, const int &);

    friend bool operator!=(const int &, const Rational &);

    friend bool operator>(const Rational &, const Rational &);

    friend bool operator>(const Rational &, const int &);

    friend bool operator>(const int &, const Rational &);

    friend bool operator>=(const Rational &, const Rational &);

    friend bool operator>=(const Rational &, const int &);

    friend bool operator>=(const int &, const Rational &);

    friend bool operator<(const Rational &, const Rational &);

    friend bool operator<(const Rational &, const int &);

    friend bool operator<(const int &, const Rational &);

    friend bool operator<=(const Rational &, const Rational &);

    friend bool operator<=(const Rational &, const int &);

    friend bool operator<=(const int &, const Rational &);

    Rational &operator++();

    Rational operator++(int notused);

    Rational &operator--();

    Rational operator--(int notused);
};

Rational::Rational() {
    this->numerator = 0;
    this->denominator = 1;
}

Rational::Rational(const int &nominator, const int &denominator) {
    this->numerator = nominator;
    this->denominator = denominator;
    this->reduce();
}

Rational::Rational(const Rational &that) {
    this->numerator = that.numerator;
    this->denominator = that.denominator;
}

void Rational::assign(const char *string) {
    int p = 0;
    int q = 0;
    int i = 0;
    int sign = 1;
    while (string[i] != '/' && string[i] != 0) {
        if (string[i] == '-')
            sign = -1;
        else
            p = p * 10 + string[i] - '0';
        i++;
    }
    p *= sign;

    if (string[i] == 0)
        q = 1;
    else {
        i++;
        while (string[i] != 0) {
            q = q * 10 + string[i] - '0';
            i++;
        }
    }

    this->numerator = p;
    this->denominator = q;
}


int Rational::getNumerator() const {
    return this->numerator;
}

int Rational::getDenominator() const {
    return this->denominator;
}

istream &operator>>(istream &in, Rational &value) {
    char str[10000];
    in >> str;
    value.assign(str);
    return in;
}

ostream &operator<<(ostream &out, const Rational &value) {
    if (value.denominator == 1) {
        out << value.numerator;
    } else {
        out << value.numerator << '/' << value.denominator;
    }
    return out;
}

Rational operator+(const Rational &a, const Rational &b) {
    Rational res;
    res.numerator = a.numerator * b.denominator + a.denominator * b.numerator;
    res.denominator = a.denominator * b.denominator;
    res.reduce();
    return res;
}

Rational operator+(const Rational &a, const int &b) {
    return a + Rational(b);
}

Rational operator+(const int &a, const Rational &b) {
    return Rational(a) + b;
}

Rational operator-(const Rational &a, const Rational &b) {
    Rational res;
    res.numerator = a.numerator * b.denominator - a.denominator * b.numerator;
    res.denominator = a.denominator * b.denominator;
    res.reduce();
    return res;
}

Rational operator-(const Rational &a, const int &b) {
    return a - Rational(b);
}

Rational operator-(const int &a, const Rational &b) {
    return Rational(a) - b;
}

Rational operator*(const Rational &a, const Rational &b) {
    Rational res;
    res.numerator = a.numerator * b.numerator;
    res.denominator = a.denominator * b.denominator;
    res.reduce();
    return res;
}

Rational operator*(const Rational &a, const int &b) {
    return a * Rational(b);
}

Rational operator*(const int &a, const Rational &b) {
    return Rational(a) * b;
}

Rational operator/(const Rational &a, const Rational &b) {
    if (b.numerator == 0) {
        throw RationalDivisionByZero();
    }
    Rational res;
    res.numerator = abs(a.numerator * b.denominator);
    res.denominator = abs(a.denominator * b.numerator);
    res.reduce();
    return res;
}

Rational operator/(const Rational &a, const int &b) {
    return a / Rational(b);
}

Rational operator/(const int &a, const Rational &b) {
    return Rational(a) / b;
}

Rational &Rational::operator=(const Rational &that) {
    this->numerator = that.numerator;
    this->denominator = that.denominator;
    return *this;
}

Rational &Rational::operator=(const int &that) {
    this->numerator = that;
    this->denominator = 1;
    return *this;
}

Rational &Rational::operator+=(const Rational &that) {
    return *this = *this + that;
}

Rational &Rational::operator+=(const int &that) {
    return *this = *this + Rational(that);
}

Rational &Rational::operator-=(const Rational &that) {
    return *this = *this - that;
}

Rational &Rational::operator-=(const int &that) {
    return *this = *this - Rational(that);
}

Rational &Rational::operator*=(const Rational &that) {
    return *this = *this * that;
}

Rational &Rational::operator*=(const int &that) {
    return *this = *this * Rational(that);
}

Rational &Rational::operator/=(const Rational &that) {
    return *this = *this / that;
}

Rational &Rational::operator/=(const int &that) {
    return *this = *this / Rational(that);
}

bool operator>(const Rational &a, const Rational &b) {
    return (a - b).numerator > 0;
}

bool operator>(const int &a, const Rational &b) {
    return Rational(a) > b;
}

bool operator>(const Rational &a, const int &b) {
    return a > Rational(b);
}

bool operator>=(const Rational &a, const Rational &b) {
    return (a - b).numerator >= 0;
}

bool operator>=(const int &a, const Rational &b) {
    return Rational(a) >= b;
}

bool operator>=(const Rational &a, const int &b) {
    return a >= Rational(b);
}

bool operator<(const Rational &a, const Rational &b) {
    return b > a;
}

bool operator<(const int &a, const Rational &b) {
    return Rational(a) < b;
}

bool operator<(const Rational &a, const int &b) {
    return a < Rational(b);
}

bool operator<=(const Rational &a, const Rational &b) {
    return (a - b).numerator <= 0;
}

bool operator<=(const int &a, const Rational &b) {
    return Rational(a) <= b;
}

bool operator<=(const Rational &a, const int &b) {
    return a <= Rational(b);
}

bool operator==(const Rational &a, const Rational &b) {
    return (a - b).numerator == 0;
}

bool operator==(const int &a, const Rational &b) {
    return Rational(a) == b;
}

bool operator==(const Rational &a, const int &b) {
    return a == Rational(b);
}

bool operator!=(const Rational &a, const Rational &b) {
    return !(a == b);
}

bool operator!=(const int &a, const Rational &b) {
    return Rational(a) != b;
}

bool operator!=(const Rational &a, const int &b) {
    return a != Rational(b);
}

Rational operator-(const Rational &that) {
    Rational res(that);
    res.numerator *= -1;
    return res;
}

Rational operator+(const Rational &that) {
    return Rational(that);
}

Rational &Rational::operator++() {
    this->numerator += this->denominator;
    return *this;
}

Rational Rational::operator++(int notused) {
    Rational tmp(*this);
    ++*this;
    return tmp;
}

Rational &Rational::operator--() {
    this->numerator -= this->denominator;
    return *this;
}

Rational Rational::operator--(int notused) {
    Rational tmp(*this);
    --*this;
    return tmp;
}

int main(int argc, char **argv) {
    int a;
    cin >> a;

    int p, q;
    cin >> p >> q;
    const Rational rc(p, q);
    cout << rc.getNumerator() << ' ' << rc.getDenominator() << endl;

    Rational r1, r2;
    cin >> r1 >> r2;

    cout << r1 << endl;
    cout << r2 << endl;


    try {
        cout << 1 / r1 << endl;
    }
    catch (const RationalDivisionByZero &ex) {
        cout << "Cannot get reciprocal of r1." << endl;
    }

    try {
        cout << rc / r2 << endl;
    } catch (const RationalDivisionByZero &ex) {
        cout << "Cannot divide by r2." << endl;
    }

    cout << (r1 < r2) << endl;
    cout << (r1 <= r2) << endl;
    cout << (r1 > r2) << endl;
    cout << (r1 >= r2) << endl;
    cout << (r1 == r2) << endl;
    cout << (r1 != r2) << endl;

    cout << (r1 < a) << endl;
    cout << (r1 <= a) << endl;
    cout << (r1 > a) << endl;
    cout << (r1 >= a) << endl;
    cout << (r1 == a) << endl;
    cout << (r1 != a) << endl;

    cout << (a < r2) << endl;
    cout << (a <= r2) << endl;
    cout << (a > r2) << endl;
    cout << (a >= r2) << endl;
    cout << (a == r2) << endl;
    cout << (a != r2) << endl;

    cout << rc + a << endl
         << a + rc << endl
         << -rc * r1 << endl
         << (+r1 - r2 * rc) * a << endl;

    cout << ++r1 << endl;
    cout << r1 << endl;
    cout << r1++ << endl;
    cout << r1 << endl;
    cout << --r1 << endl;
    cout << r1 << endl;
    cout << r1-- << endl;
    cout << r1 << endl;
    cout << ++ ++r1 << endl;
    cout << r1 << endl;

    cout << ((((r1 += r2) /= Rational(-5, 3)) -= rc) *= a) << endl;
    cout << (r1 += r2 /= 3) << endl;
    cout << r1 << endl;
    cout << r2 << endl;
    return 0;
}