//
// Created by Artyom on 15.03.2017.
//

#include "BigInt.h"
#include <math.h>


BigIntegerDivisionByZero::BigIntegerDivisionByZero() : logic_error("Division by zero") {};

BigIntegerOverflow::BigIntegerOverflow() : overflow_error("Over flow") {};


BigInteger::BigInteger() {
    this->capacity = 0;
    this->sign = 1;
}

BigInteger::BigInteger(const long long &value) {
    long long tmp = ::abs(value);

    if (value < 0)
        this->sign = -1;
    else
        this->sign = 1;

    int v = BASE;
    int n = 1;
    while (v <= tmp) {
        v *= BASE;
        n++;
    }
    set_capacity(n);
    for (int i = 0; i < this->capacity; i++) {
        this->values[i] = int(tmp % BASE);
        tmp /= BASE;
    }
}

void BigInteger::set_capacity(const int capacity) {
    if (capacity > BigInteger::MAX)
        throw BigIntegerOverflow();
    this->capacity = capacity;
    this->values = new int[this->capacity];
}

BigInteger::~BigInteger() {
    delete[]this->values;
}

void BigInteger::debug() {
    std::cout << "(capacity: " << this->capacity;
    for (int i = 0; i < this->capacity; ++i) {
        std::cout << "[" << i << ":" << this->values[i] << "]";
    }
    std::cout << ")\n";
}

BigInteger::BigInteger(const char *string) {
    assign(string);
}

BigInteger::BigInteger(const BigInteger &that) {
    this->sign = that.sign;
    set_capacity(that.capacity);
    std::memcpy(this->values, that.values, this->capacity * sizeof(int));
}

std::ostream &operator<<(std::ostream &out, const BigInteger &value) {
    int size = value.get_length();

    if (size == 0)
        out << '0';
    else {
        if (value.sign == -1)
            out << '-';


        for (int i = size - 1; i >= 0; --i) {
            int &v = value.values[i];
            int d = value.BASE / 10;
            while (i < size - 1 && d > v + 1) {
                out << '0';
                d /= 10;
            }
            out << v;
        }
    }
    return out;
}

std::istream &operator>>(std::istream &in, BigInteger &value) {
    char str[100000];
    in >> str;
    value.assign(str);
    return in;
}

void BigInteger::assign(const char *string) {
    int len = strlen(string);
    int p = 0;

    if (string[0] == '-') {
        p = 1;
        this->sign = -1;
        --len;
    } else
        this->sign = 1;

    set_capacity(len / DIGIT_COUNT + 1);
    for (int i = 0; i < this->capacity; ++i) {
        int value = 0;
        for (int j = len - (i + 1) * DIGIT_COUNT + p; j < len - i * DIGIT_COUNT + p; j++) {
            if (j >= 0 && string[j] != '-') {
                value = (value * 10) + (string[j] - '0');
            }
        }
        values[i] = value;
    }
}

int BigInteger::get_length() const {
    int length = this->capacity;
    while (length > 0 && this->values[length - 1] == 0)
        --length;
    return length;
}

BigInteger::BigInteger(const size_t &size) {
    this->set_capacity(size);
    for (int i = 0; i < size; ++i)
        this->values[i] = 0;
}

BigInteger abs_plus(const BigInteger &a, const BigInteger &b, int sign) {
    int new_size;
    if (a.capacity > b.capacity)
        new_size = a.capacity;
    else
        new_size = b.capacity;

    BigInteger c((size_t) new_size);
    int sum = 0;
    int remainder = 0;
    for (int i = 0; i < c.capacity || remainder; ++i) {
        sum = 0;
        if (i < a.capacity)
            sum = sum + a.values[i];
        if (i < b.capacity)
            sum = sum + b.values[i];
        c.values[i] = (sum + remainder) % c.BASE;
        remainder = (remainder + sum) / c.BASE;
    }
    c.sign = sign;
    if (c.get_length() > BigInteger::MAX)
        throw BigIntegerOverflow();

    return c;
}


BigInteger BigInteger::abs() const {
    BigInteger res(*this);
    res.sign = 1;
    return res;
}

BigInteger abs_minus(const BigInteger &a, const BigInteger &b, int sign) {
    if (a.capacity >= b.capacity) {
        BigInteger c((size_t) a.capacity);
        for (int i = 0; i < a.capacity; i++) {
            c.values[i] = a.values[i];
            if (i < b.capacity)
                if (a.values[i] < b.values[i] && i != a.capacity - 1) {
                    int diff = a.values[i] - b.values[i];
                    c.values[i] = c.BASE + diff;
                    --a.values[i + 1];
                } else if (a.values[i] < b.values[i] && i == a.capacity - 1)
                    c.values[i] = abs(a.values[i] - b.values[i]);
                else
                    c.values[i] = a.values[i] - b.values[i];
        }
        c.sign = sign;
        if (c.get_length() > BigInteger::MAX)
            throw BigIntegerOverflow();
        return c;
    } else
        return abs_minus(b, a, sign);
}

BigInteger operator+(const BigInteger &a, const BigInteger &b) {
    if (a.sign == b.sign)
        return abs_plus(a, b, a.sign);
    else {
        if (!(a.abs() <= b.abs()))
            return abs_minus(a, b, a.sign);
        else
            return abs_minus(b, a, b.sign);
    }
}

BigInteger operator+(const long long &a, const BigInteger &b) {
    return BigInteger(a) + a;
}

BigInteger operator+(const BigInteger &a, const long long &b) {
    return BigInteger(b) + a;
}

BigInteger &BigInteger::operator=(const BigInteger &that) {
    this->sign = that.sign;
    if (that.capacity > this->capacity) {
        delete[]this->values;
        set_capacity(that.capacity);
    }
    std::memcpy(this->values, that.values, that.capacity * sizeof(int));
    for (int i = this->capacity - 1; i >= that.capacity; --i) {
        this->values[i] = 0;
    }
    return *this;

}

BigInteger &BigInteger::operator=(const char *s) {
    delete[]this->values;
    this->assign(s);
    return *this;
}

BigInteger &BigInteger::operator=(const long long &value) {
    delete[]this->values;

    long long tmp = ::abs(value);

    if (value < 0)
        this->sign = -1;
    else
        this->sign = 1;

    int v = BASE;
    int n = 1;
    while (v < tmp) {
        v *= BASE;
        n++;
    }
    set_capacity(n);
    for (int i = 0; i < this->capacity; i++) {
        this->values[i] = (int) tmp % BASE;
        tmp /= BASE;
    }
    return *this;
}

BigInteger &BigInteger::operator+=(const BigInteger &that) {
    return *this = *this + that;
}

BigInteger &BigInteger::operator+=(const long long &that) {
    *this = *this + that;
    return *this;
}

BigInteger operator-(const BigInteger &a, const BigInteger &b) {
    if (a.sign == b.sign) {
        if (!(a.abs() <= b.abs()))
            return abs_minus(a, b, a.sign);
        else
            return abs_minus(b, a, b.sign * -1);
    } else
        return abs_plus(a, b, a.sign);
}

BigInteger BigInteger::operator-() {
    BigInteger res(*this);
    res.sign *= -1;
    return res;
}

BigInteger operator-(const long long &a, const BigInteger &b) {
    return BigInteger(a) - b;
}

BigInteger operator-(const BigInteger &a, const long long &b) {
    return BigInteger(b) - a;
}


BigInteger operator*(const BigInteger &a, const BigInteger &b) {
    int length = a.capacity + b.capacity + 1;
    BigInteger c((size_t) length);
    for (int i = 0; i < a.capacity; i++) {
        int remainder = 0;
        for (int j = 0; j < b.capacity || remainder; j++) {
            long long current_value = c.values[i + j] + a.values[i] * (j < b.capacity ? b.values[j] : 0) + remainder;
            c.values[i + j] += a.values[i] * b.values[j] + remainder;
            remainder = (int) current_value / BigInteger::BASE;
            c.values[i + j] = (int) current_value % BigInteger::BASE;
        }
    }
    c.sign = a.sign * b.sign;
    if (c.get_length() > BigInteger::MAX)
        throw BigIntegerOverflow();
    return c;
}

BigInteger operator*(const BigInteger &a, const long long &b) {
    return BigInteger(b) * a;
}

BigInteger operator*(const long long &a, const BigInteger &b) {
    return BigInteger(a) * b;
}


bool operator<=(const BigInteger &a, const BigInteger &b) {
    if (a.get_length() != b.get_length())
        return a.get_length() < b.get_length();

    for (int i = a.get_length() - 1; i >= 0; i--) {
        if (a.values[i] != b.values[i])
            return a.values[i] < b.values[i];
    }
    return true;
}

BigInteger operator/(const BigInteger &a, const BigInteger &b) {
    BigInteger o("0");
    if (b == o)
        throw BigIntegerDivisionByZero();
    else {

        if (a.abs() <= b.abs() && !(a.abs() == b.abs())) {
            BigInteger res = "0";
            return res;
        }
        int length1 = a.get_length();
        int length2 = b.get_length();
        BigInteger res((size_t) length1 - length2 + 1);
        BigInteger currentValue((size_t) length2 + 1);
        res.sign = a.sign * b.sign;

        for (int i = length1 - length2; i < length1; i++) {
            currentValue.values[i - length1 + length2] = a.values[i];
        }
        int diff_length = length1 - length2;
        int res_value;
        currentValue.debug();

        while (diff_length >= 0) {
            res_value = 0;
            while (b <= currentValue) {
                currentValue = abs_minus(currentValue, b, 1);
                res_value++;
            }
            res.values[diff_length] = res_value;
            if (diff_length > 0) {
                for (int i = length2 - 1; i >= 0; i--) {
                    currentValue.values[i + 1] = currentValue.values[i];
                }
                currentValue.values[0] = a.values[diff_length - 1];
            }
            diff_length--;
        }
        return res;
    }
}


bool operator==(const BigInteger &a, const BigInteger &b) {
    if (a.sign != b.sign || a.get_length() != b.get_length())
        return false;
    int len1 = a.get_length();
    for (int i = 0; i < len1; i++) {
        if (a.values[i] != b.values[i])
            return false;
    }
    return true;
}

BigInteger &BigInteger::operator-=(const BigInteger &that) {
    return *this = *this - that;
}

BigInteger &BigInteger::operator-=(const long long &that) {
    return *this = *this - that;
}

BigInteger &BigInteger::operator*=(const BigInteger &that) {
    return *this = *this * that;
}

BigInteger &BigInteger::operator*=(const long long &that) {
    return *this = *this * that;
}

BigInteger operator/(const BigInteger &a, const long long &b) {
    return a / BigInteger(b);
}

BigInteger operator/(const long long &a, const BigInteger &b) {
    return BigInteger(a) / b;
}

BigInteger &BigInteger::operator/=(const BigInteger &that) {
    return *this = *this / that;
}

BigInteger &BigInteger::operator/=(const long long &that) {
    return *this = *this / that;
}

BigInteger BigInteger::operator++() {
    return *this = *this + 1;
}

BigInteger BigInteger::operator++(int notused) {
    BigInteger temp = *this;
    temp = temp + 1;
    return temp;
}

BigInteger BigInteger::operator--() {
    return *this = *this - 1;
}

BigInteger BigInteger::operator--(int notused) {
    BigInteger temp = *this;
    temp = temp - 1;
    return temp;
}





















