//
// Created by Artyom on 01.04.2017.
//

#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <cstring>

using namespace std;

class MatrixAllocationError {
};

class MatrixWrongSizeError {
};

class MatrixIndexError {
};

class MatrixIsDegenerateError {
};

template<typename T>
T getZero() {
    return T(0);
}

template<typename T>
T getOne() {
    return T(1);
}


template<typename T>
class Matrix {
private:
    int row_count;
    int col_count;
    T **values;

protected:
    Matrix();

    void set_sizes(const int row_count, const int col_count);

    void free_values();

    virtual void assign(const Matrix<T> &that);


    static bool compare_size(const Matrix<T> &matrix1, const Matrix<T> &matrix2);


    void swap_rows(const int, const int);

public:
    Matrix(const int row_count, const int col_count);

    Matrix(const Matrix<T> &that);

    virtual ~Matrix();

    Matrix<T> &operator=(const Matrix<T> &that);

    Matrix<T> operator+(const Matrix<T> &that) const;

    Matrix<T> operator-(const Matrix<T> &that) const;

    Matrix<T> operator*(const T &coefficient) const;

    Matrix<T> operator*(const Matrix<T> &) const;

    Matrix<T> &operator+=(const Matrix<T> &);

    Matrix<T> &operator-=(const Matrix<T> &);

    Matrix<T> &operator*=(const Matrix<T> &);

    Matrix<T> &operator*=(const T);

    template<typename C>
    friend Matrix<C> operator*(const C &coefficient, const Matrix<C> matrix);

    template<typename C>
    friend std::ostream &operator<<(std::ostream &out, const Matrix<C> &matrix);

    template<typename C>
    friend std::istream &operator>>(std::istream &in, const Matrix<C> &matrix);

    T operator()(const int, const int) const;

    T &operator()(const int, const int);

    int rows_size() const;

    int columns_size() const;

    Matrix<T> getTransposed() const;

    Matrix<T> &transpose();
};

template<typename T>
class SquareMatrix : public Matrix<T> {
protected:
    void assign(const Matrix<T> &that);

    SquareMatrix<T> get_minor(const int, const int) const;

public:
    SquareMatrix(const int size);

    SquareMatrix(const Matrix<T> &that);

    T getDeterminant() const;

    SquareMatrix<T> operator=(const SquareMatrix<T> &that);

    SquareMatrix<T> operator+(const SquareMatrix<T> &that) const;

    SquareMatrix<T> operator-(const SquareMatrix<T> &that) const;

    SquareMatrix<T> operator*(const T &coefficient) const;

    SquareMatrix<T> operator*(const SquareMatrix<T> &that) const;

    SquareMatrix<T> &operator+=(const SquareMatrix<T> &);

    SquareMatrix<T> &operator-=(const SquareMatrix<T> &);

    SquareMatrix<T> &operator*=(const SquareMatrix<T> &);

    SquareMatrix<T> &operator*=(const T);

    template<typename C>
    friend SquareMatrix<C> operator*(const C &coefficient, const SquareMatrix<C> matrix);

    SquareMatrix<T> getInverse() const;

    SquareMatrix<T> &invert();

    SquareMatrix<T> &transpose();

    SquareMatrix<T> getTransposed() const;

    T getTrace() const;

    int getSize() const;
};

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


template<typename T>
Matrix<T>::Matrix(const int row_count, const int col_count) {
    set_sizes(row_count, col_count);
    for (int row = 0; row < row_count; ++row) {
        for (int col = 0; col < col_count; ++col) {
            this->values[row][col] = 0;
        }
    }
}

template<typename T>
void Matrix<T>::set_sizes(const int row_count, const int col_count) {
    this->row_count = row_count;
    this->col_count = col_count;
    this->values = new T *[row_count];
    for (int row = 0; row < row_count; ++row) {
        this->values[row] = new T[col_count];
        for (int col = 0; col < col_count; ++col)
            values[row][col] = 0;
    }
}

template<typename T>
Matrix<T>::Matrix(const Matrix &that) {
    assign(that);
}

template<typename T>
Matrix<T>::~Matrix() {
    free_values();
}

template<typename T>
void Matrix<T>::free_values() {
    for (int row = 0; row < row_count; ++row) {
        delete[]this->values[row];
    }
    delete[]this->values;
    this->col_count = 0;
    this->row_count = 0;
}


template<typename T>
bool Matrix<T>::compare_size(const Matrix<T> &matrix1, const Matrix<T> &matrix2) {
    return (matrix1.row_count == matrix2.row_count) && (matrix1.col_count == matrix2.col_count);
}

template<typename C>
std::ostream &operator<<(std::ostream &out, const Matrix<C> &matrix) {
    for (int row = 0; row < matrix.row_count; ++row) {
        for (int col = 0; col < matrix.col_count; ++col) {
            out << matrix.values[row][col] << " ";
        }
        out << std::endl;
    }
    return out;
}

template<typename C>
std::istream &operator>>(std::istream &in, const Matrix<C> &matrix) {
    for (int row = 0; row < matrix.row_count; ++row) {
        for (int col = 0; col < matrix.col_count; ++col) {
            in >> matrix.values[row][col];
        }
    }
    return in;
}

template<typename T>
Matrix<T> &Matrix<T>::operator=(const Matrix<T> &that) {
    if (this != &that) {
        this->free_values();
        this->assign(that);
    }
    return *this;
}

template<typename T>
void Matrix<T>::assign(const Matrix<T> &that) {
    this->set_sizes(that.row_count, that.col_count);
    for (int row = 0; row < that.row_count; ++row) {
        for (int col = 0; col < that.col_count; ++col) {
            this->values[row][col] = that.values[row][col];
        }
    }
}

template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix &that) const {
    if (!Matrix::compare_size(*this, that)) {
        throw MatrixWrongSizeError();
    }
    Matrix<T> result(this->row_count, this->col_count);
    for (int row = 0; row < row_count; ++row) {
        for (int col = 0; col < col_count; ++col) {
            result.values[row][col] = this->values[row][col] + that.values[row][col];
        }
    }
    return result;
}

template<typename T>
Matrix<T> Matrix<T>::operator-(const Matrix &that) const {
    if (!Matrix::compare_size(*this, that)) {
        throw MatrixWrongSizeError();
    }
    Matrix<T> result(this->row_count, this->col_count);
    for (int row = 0; row < row_count; ++row) {
        for (int col = 0; col < col_count; ++col) {
            result.values[row][col] = this->values[row][col] - that.values[row][col];
        }
    }
    return result;
}

template<typename T>
Matrix<T>::Matrix() {
    this->set_sizes(1, 1);
}

template<typename T>
int Matrix<T>::rows_size() const {
    return row_count;
}

template<typename T>
int Matrix<T>::columns_size() const {
    return col_count;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const T &coefficient) const {
    Matrix<T> result(this->row_count, this->col_count);
    for (int row = 0; row < row_count; ++row) {
        for (int col = 0; col < col_count; ++col) {
            result.values[row][col] = this->values[row][col] * coefficient;
        }
    }
    return result;
}

template<typename C>
Matrix<C> operator*(const C &coefficient, const Matrix<C> matrix) {
    return matrix * coefficient;
}


template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T> &matrix2) const {
    if (this->col_count != matrix2.row_count) {
        throw MatrixWrongSizeError();
    }
    Matrix<T> result(this->row_count, matrix2.col_count);
    for (int row = 0; row < this->row_count; ++row) {
        for (int col = 0; col < matrix2.col_count; ++col) {
            result.values[row][col] = 0;
            for (int i = 0; i < this->col_count; i++) {
                result.values[row][col] += this->values[row][i] * matrix2.values[i][col];
            }
        }
    }
    return result;
}

template<typename T>
Matrix<T> &Matrix<T>::operator+=(const Matrix<T> &that) {
    *this = *this + that;
    return *this;
}

template<typename T>
Matrix<T> &Matrix<T>::operator-=(const Matrix<T> &that) {
    *this = *this - that;
    return *this;
}

template<typename T>
Matrix<T> &Matrix<T>::operator*=(const Matrix<T> &that) {
    *this = *this * that;
    return *this;
}

template<typename T>
Matrix<T> &Matrix<T>::operator*=(const T that) {
    *this = *this * that;
    return *this;
}

template<typename T>
void Matrix<T>::swap_rows(const int first_row, const int second_row) {
    for (int i = 0; i < this->col_count; i++) {
        T temp = this->values[first_row][i];
        this->values[first_row][i] = this->values[second_row][i];
        this->values[second_row][i] = -temp;
    }
}

template<typename T>
T Matrix<T>::operator()(const int row, const int column) const {
    if (row >= this->row_count || column >= this->col_count) {
        throw MatrixIndexError();
    }
    return this->values[row][column];
}

template<typename T>
T &Matrix<T>::operator()(const int row, const int column) {
    if (row >= this->row_count || column >= this->col_count) {
        throw MatrixIndexError();
    }
    return this->values[row][column];
}

template<typename T>
Matrix<T> Matrix<T>::getTransposed() const {
    Matrix<T> result(this->col_count, this->row_count);
    for (int row = 0; row < this->row_count; ++row) {
        for (int col = 0; col < this->col_count; ++col) {
            result.values[col][row] = this->values[row][col];
        }
    }
    return result;
}

template<typename T>
Matrix<T> &Matrix<T>::transpose() {
    *this = this->getTransposed();
    return *this;
}

template<typename T>
void SquareMatrix<T>::assign(const Matrix<T> &that) {
    this->Matrix<T>::assign(that);
}

template<typename T>
SquareMatrix<T>::SquareMatrix(const int size) {
    this->set_sizes(size, size);
}

template<typename T>
SquareMatrix<T>::SquareMatrix(const Matrix<T> &that) {
    this->assign(that);
}

template<typename T>
SquareMatrix<T> SquareMatrix<T>::operator=(const SquareMatrix<T> &that) {
    if (this != &that) {
        this->free_values();
        this->assign(that);
    }
    return *this;
}


template<typename T>
SquareMatrix<T> SquareMatrix<T>::operator+(const SquareMatrix<T> &that) const {
    return Matrix<T>::operator+(that);
}

template<typename T>
SquareMatrix<T> SquareMatrix<T>::operator-(const SquareMatrix<T> &that) const {
    return Matrix<T>::operator-(that);
}

template<typename T>
SquareMatrix<T> SquareMatrix<T>::operator*(const SquareMatrix<T> &that) const {
    return Matrix<T>::operator*(that);
}

template<typename T>
SquareMatrix<T> SquareMatrix<T>::operator*(const T &coefficient) const {
    return Matrix<T>::operator*(coefficient);
}

template<typename C>
SquareMatrix<C> operator*(const C &coefficient, const SquareMatrix<C> matrix) {
    return matrix * coefficient;
}

template<typename T>
SquareMatrix<T> &SquareMatrix<T>::operator+=(const SquareMatrix<T> &that) {
    return *this = *this + that;
}

template<typename T>
SquareMatrix<T> &SquareMatrix<T>::operator-=(const SquareMatrix<T> &that) {
    return *this = *this - that;;
}

template<typename T>
SquareMatrix<T> &SquareMatrix<T>::operator*=(const SquareMatrix<T> &that) {
    *this = *this * that;
    return *this;
}

template<typename T>
SquareMatrix<T> &SquareMatrix<T>::operator*=(const T coefficient) {
    return *this = *this * coefficient;
}

template<typename T>
int SquareMatrix<T>::getSize() const {
    return this->rows_size();
}

template<typename T>
SquareMatrix<T> SquareMatrix<T>::getTransposed() const {
    return Matrix<T>::getTransposed();
}

template<typename T>
SquareMatrix<T> &SquareMatrix<T>::transpose() {
    *this = this->getTransposed();
    return *this;
}

template<typename T>
T SquareMatrix<T>::getDeterminant() const {
    SquareMatrix<T> temp = *this;
    T ans = 1;
    for (int col = 0; col < temp.columns_size(); ++col) {
        int row = col;
        while (row < temp.rows_size() && temp.operator()(row, col) == 0) {
            row++;
        }
        if (row == temp.rows_size()) {
            return 0;
        }

        if (row != col) {
            temp.swap_rows(col, row);
        }

        ans *= temp.operator()(col, col);
        for (int k = col + 1; k < temp.rows_size(); k++) {
            T coefficient = temp.operator()(k, col) / temp.operator()(col, col);
            for (int i = col; i < temp.columns_size(); ++i)
                temp.operator()(k, i) -= coefficient * temp.operator()(col, i);
        }
    }

    return ans;
}


template<typename T>
SquareMatrix<T> SquareMatrix<T>::get_minor(const int _row, const int _col) const {
    SquareMatrix<T> result(this->getSize() - 1);
    for (int row = 0; row < this->rows_size(); ++row) {
        for (int col = 0; col < this->columns_size(); col++) {
            if (row != _row && col != _col) {
                int i = row;
                int j = col;
                if (row > _row) {
                    i = row - 1;
                }
                if (col > _col) {
                    j = col - 1;
                }
                result.operator()(i, j) = this->operator()(row, col);
            }
        }
    }
    return result;
}

template<typename T>
T SquareMatrix<T>::getTrace() const {
    T ans = T(0);
    for (int row = 0; row < this->rows_size(); ++row) {
        ans += this->operator()(row, row);
    }
    return ans;
}

template<typename T>
SquareMatrix<T> SquareMatrix<T>::getInverse() const {
    if (this->getDeterminant() == 0) {
        throw MatrixIsDegenerateError();
    }
    SquareMatrix<T> result(this->getSize());
    T this_det = this->getDeterminant();
    for (int row = 0; row < this->rows_size(); row++) {
        for (int col = 0; col < this->columns_size(); col++) {
            result.operator()(row, col) =
                    this->get_minor(row, col).getDeterminant() / this_det * ((row + col) % 2 == 1 ? -1 : 1);
        }
    }

    result.transpose();
    return result;
}

template<typename T>
SquareMatrix<T> &SquareMatrix<T>::invert() {
    *this = this->getInverse();
    return *this;
}


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

int main() {
    int m, n, p, q;
    cin >> m >> n >> p >> q;

    Matrix<int> A(m, n), B(p, q);
    cin >> A >> B;

    A = A;
    try {
        cout << A + B * 2 - m * A << endl;
        cout << (A -= B += A *= 2) << endl;
        cout << (((A -= B) += A) *= 2) << endl;
    } catch (const MatrixWrongSizeError &) {
        cout << "A and B are of different size." << endl;
    }
    B = A;
    cout << B << endl;

    Rational r;
    cin >> r;
    Matrix<Rational> C(m, n), D(p, q);
    cin >> C >> D;
    try {
        cout << C * D << endl;
        cout << (C *= D) << endl;
        cout << C << endl;
    } catch (const MatrixWrongSizeError &) {
        cout << "C and D have not appropriate sizes for multiplication." << endl;
    }
    cout << C.getTransposed() * (r * C) << endl;
    cout << C.transpose() << endl;
    cout << C << endl;

    SquareMatrix<Rational> S(m);
    cin >> S;
    SquareMatrix<Rational> P(S);
    const SquareMatrix<Rational> &rS = S;
    cout << rS.getSize() << ' ' << rS.getDeterminant() << ' ' << rS.getTrace() << endl;
    cout << (S = S) * (S + rS) << endl;
    cout << (S *= S) << endl;
    C.transpose();
    cout << rS * C << endl;
    cout << S << endl;
    S = P;
    cout << (Rational(1, 2) * S).getDeterminant() << endl;
    try {
        cout << rS(0, 0) << endl;
        (S(0, 0) *= 2) /= 2;
        cout << rS(0, m) << endl;
    } catch (const MatrixIndexError &) {
        cout << "Index out of range." << endl;
    }
    cout << rS.getTransposed() << endl;
    try {
        cout << rS.getInverse() << endl;
        cout << S.invert().getTransposed().getDeterminant() << endl;
        cout << S << endl;
    } catch (const MatrixIsDegenerateError &) {
        cout << "Cannot inverse S." << endl;
    }
    return 0;
}
