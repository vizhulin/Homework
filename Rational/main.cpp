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
    int nominator;
    int denominator;

    void assign(const char *);

    void reduce() {
        int a = abs(nominator);
        int b = abs(denominator);
        while (b) {
            a = a % b;
            swap(a, b);
        }
        nominator /= a;
        denominator /= a;
    }

public:
    Rational();

    Rational(const int &, const int &);

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
    this->nominator = 0;
    this->denominator = 1;
}

Rational::Rational(const int &nominator, const int &denominator) {
    int sign = 1;
    if (nominator * denominator < 0)
        sign = -1;

    this->nominator = abs(nominator) * sign;
    this->denominator = abs(denominator);
    this->reduce();
}

Rational::Rational(const Rational &that) {
    this->nominator = that.nominator;
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

    this->nominator = p;
    this->denominator = q;
}


int Rational::getNumerator() const {
    return this->nominator;
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
        out << value.nominator;
    } else {
        out << value.nominator << '/' << value.denominator;
    }
    return out;
}

Rational operator+(const Rational &a, const Rational &b) {
    Rational res;
    res.nominator = a.nominator * b.denominator + a.denominator * b.nominator;
    res.denominator = a.denominator * b.denominator;
    res.reduce();
    return res;
}

Rational operator+(const Rational &a, const int &b) {
    return a + Rational(b, 1);
}

Rational operator+(const int &a, const Rational &b) {
    return Rational(a, 1) + b;
}

Rational operator-(const Rational &a, const Rational &b) {
    Rational res;
    res.nominator = a.nominator * b.denominator - a.denominator * b.nominator;
    res.denominator = a.denominator * b.denominator;
    res.reduce();
    return res;
}

Rational operator-(const Rational &a, const int &b) {
    return a - Rational(b, 1);
}

Rational operator-(const int &a, const Rational &b) {
    return Rational(a, 1) - b;
}

Rational operator*(const Rational &a, const Rational &b) {
    Rational res;
    res.nominator = a.nominator * b.nominator;
    res.denominator = a.denominator * b.denominator;
    res.reduce();
    return res;
}

Rational operator*(const Rational &a, const int &b) {
    return a * Rational(b, 1);
}

Rational operator*(const int &a, const Rational &b) {
    return Rational(a, 1) * b;
}

Rational operator/(const Rational &a, const Rational &b) {
    if (b.nominator == 0) {
        throw RationalDivisionByZero();
    }
    Rational res;
    int sign = 1;
    if (a.nominator * b.nominator < 0) {
        sign = -1;
    }
    res.nominator = abs(a.nominator * b.denominator) * sign;
    res.denominator = abs(a.denominator * b.nominator);
    res.reduce();
    return res;
}

Rational operator/(const Rational &a, const int &b) {
    return a / Rational(b, 1);
}

Rational operator/(const int &a, const Rational &b) {
    return Rational(a, 1) / b;
}

Rational &Rational::operator=(const Rational &that) {
    this->nominator = that.nominator;
    this->denominator = that.denominator;
    return *this;
}

Rational &Rational::operator=(const int &that) {
    this->nominator = that;
    this->denominator = 1;
    return *this;
}

Rational &Rational::operator+=(const Rational &that) {
    return *this = *this + that;
}

Rational &Rational::operator+=(const int &that) {
    return *this = *this + Rational(that, 1);
}

Rational &Rational::operator-=(const Rational &that) {
    return *this = *this - that;
}

Rational &Rational::operator-=(const int &that) {
    return *this = *this - Rational(that, 1);
}

Rational &Rational::operator*=(const Rational &that) {
    return *this = *this * that;
}

Rational &Rational::operator*=(const int &that) {
    return *this = *this * Rational(that, 1);
}

Rational &Rational::operator/=(const Rational &that) {
    return *this = *this / that;
}

Rational &Rational::operator/=(const int &that) {
    return *this = *this / Rational(that, 1);
}

bool operator>(const Rational &a, const Rational &b) {
    if (a.nominator * b.denominator > a.denominator * b.nominator) {
        return true;
    } else if (a.nominator * b.denominator == a.denominator * b.nominator) {
        return false;
    } else
        return false;
}

bool operator>(const int &a, const Rational &b) {
    return Rational(a, 1) > b;
}

bool operator>(const Rational &a, const int &b) {
    return a > Rational(b, 1);
}

bool operator>=(const Rational &a, const Rational &b) {
    if (a > b || a == b)
        return true;
    else
        return false;
}

bool operator>=(const int &a, const Rational &b) {
    return Rational(a, 1) >= b;
}

bool operator>=(const Rational &a, const int &b) {
    return a >= Rational(b, 1);
}

bool operator<(const Rational &a, const Rational &b) {
    return b > a;
}

bool operator<(const int &a, const Rational &b) {
    return Rational(a, 1) < b;
}

bool operator<(const Rational &a, const int &b) {
    return a < Rational(b, 1);
}

bool operator<=(const Rational &a, const Rational &b) {
    if (a == b || a < b)
        return true;
    else
        return false;
}

bool operator<=(const int &a, const Rational &b) {
    return Rational(a, 1) <= b;
}

bool operator<=(const Rational &a, const int &b) {
    return a <= Rational(b, 1);
}

bool operator==(const Rational &a, const Rational &b) {
    if (a.nominator == b.nominator && a.denominator == b.denominator)
        return true;
    else
        return false;
}

bool operator==(const int &a, const Rational &b) {
    return Rational(a, 1) == b;
}

bool operator==(const Rational &a, const int &b) {
    return a == Rational(b, 1);
}

bool operator!=(const Rational &a, const Rational &b) {
    return !(a == b);
}

bool operator!=(const int &a, const Rational &b) {
    return Rational(a, 1) != b;
}

bool operator!=(const Rational &a, const int &b) {
    return a != Rational(b, 1);
}

Rational operator-(const Rational &that) {
    Rational res(that);
    res.nominator *= -1;
    return res;
}

Rational operator+(const Rational &that) {
    Rational res(that);
    return res;
}

Rational &Rational::operator++() {
    this->nominator += this->denominator;
    return *this;
}

Rational Rational::operator++(int notused) {
    Rational tmp(*this);
    ++*this;
    return tmp;
}

Rational &Rational::operator--() {
    this->nominator -= this->denominator;
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