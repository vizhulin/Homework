//
// Created by Artyom on 15.03.2017.
//

#ifndef BIGINT_BIGINT_H
#define BIGINT_BIGINT_H

#include <iostream>
#include <cstring>
#include <stdexcept>
#include <iostream>

class BigInteger {
private:
    static const int BASE = 10;
    static const int DIGIT_COUNT = 1;
    static const int MAX = 1000000;

    int capacity;
    int *values;
    int sign;

    void set_capacity(const int);

    void assign(const char *);

    int get_length() const;

public:
    BigInteger();

    BigInteger(const long long &);

    BigInteger(const char *);

    BigInteger(const BigInteger &);

    BigInteger(const size_t &);

    ~BigInteger();

    void debug();

    friend std::ostream &operator<<(std::ostream &, const BigInteger &);

    friend std::istream &operator>>(std::istream &, BigInteger &);

    friend BigInteger operator+(const BigInteger &, const BigInteger &);

    friend BigInteger operator+(const long long &, const BigInteger &);

    friend BigInteger operator+(const BigInteger &, const long long &);

    friend BigInteger operator-(const BigInteger &, const BigInteger &);

    friend BigInteger operator-(const long long &, const BigInteger &);

    friend BigInteger operator-(const BigInteger &, const long long &);

    BigInteger &operator+=(const BigInteger &);

    BigInteger &operator+=(const long long &);

    BigInteger &operator-=(const BigInteger &);

    BigInteger &operator-=(const long long &);

    BigInteger &operator*=(const BigInteger &);

    BigInteger &operator*=(const long long &);

    BigInteger &operator/=(const BigInteger &);

    BigInteger &operator/=(const long long &);

    BigInteger &operator=(const BigInteger &);

    BigInteger &operator=(const char *);

    BigInteger &operator=(const long long &);

    BigInteger operator-();

    friend BigInteger operator*(const BigInteger &, const BigInteger &);

    friend BigInteger operator*(const long long &, const BigInteger &);

    friend BigInteger operator*(const BigInteger &, const long long &);

    friend BigInteger abs_plus(const BigInteger &, const BigInteger &, int);

    friend BigInteger abs_minus(const BigInteger &, const BigInteger &, int);

    friend BigInteger operator/(const BigInteger &, const long long &);

    friend BigInteger operator/(const BigInteger &, const BigInteger &);

    friend BigInteger operator/(const long long &, const BigInteger &);

    BigInteger abs() const;

    friend bool operator==(const BigInteger &, const BigInteger &);

    friend bool operator<=(const BigInteger &, const BigInteger &);

    BigInteger operator++();

    BigInteger operator++(int notused);

    BigInteger operator--();

    BigInteger operator--(int notused);


};

class BigIntegerDivisionByZero : std::logic_error {
public:
    BigIntegerDivisionByZero();
};

class BigIntegerOverflow : std::overflow_error {
public:
    BigIntegerOverflow();
};


#endif //BIGINT_BIGINT_H
