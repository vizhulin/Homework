//
// Created by Artyom on 01.04.2017.
//

#ifndef HOMEWORK_GEOMETRY_H
#define HOMEWORK_GEOMETRY_H

#include <iostream>
#include <cstdlib>
#include <iostream>
#include <cmath>

using namespace std;

class Point;

class Segment;

class Line;

class Ray;

class Vector {
private:
    double x;
    double y;
public:
    Vector() : x(0), y(0) {};

    Vector(const double &x, double &y) : x(x), y(y) {};

    Vector(const Vector &that) : x(that.x), y(that.y) {};

    Vector(const Point &, const Point &);

    double get_x() const { return this->x; };

    double get_y() const { return this->y; };

    friend double abs(const Vector &);

    friend istream &operator>>(istream &, Vector &);

    friend ostream &operator<<(ostream &, const Vector &);

    Vector operator+(const Vector &);

    Vector operator-(const Vector &);

    double operator*(const Vector &);

    friend double vector_product(const Vector &, const Vector &);
};

class Figure {
public:
    virtual void shift(const Vector &)  = 0;

    virtual bool contains_point(const Point &) const = 0;

    virtual bool cross_segment(const Segment &) const = 0;
};

class Point : public Figure {
private:
    double x;
    double y;
public:
    Point() : x(0), y(0) {};

    Point(const double &x, const double &y) : x(x), y(y) {};

    double get_x() const { return this->x; };

    double get_y() const { return this->y; };

    void shift(const Vector &);

    bool contains_point(const Point &) const;

    bool cross_segment(const Segment &) const;

    Point &operator=(const Point &);

    friend istream &operator>>(istream &, Point &);

    friend ostream &operator<<(ostream &, const Point &);

};

class Segment : public Figure {
private:
    Point begining;
    Point end;
public:
    Segment() : begining(0, 0), end(0, 0) {};

    Segment(const Point &a, const Point &b) : begining(a), end(b) {};

    Point get_begining() const { return this->begining; };

    Point get_end() const { return this->end; };

    //Segment &operator=(const Segment &);

    void shift(const Vector &);

    bool contains_point(const Point &) const;

    bool cross_segment(const Segment &) const;

};

class Line : public Figure {
private:
    double a;
    double b;
    double c;
public:
    Line() : a(0), b(0), c(0) {};

    Line(const double &a, const double &b, const double &c) : a(a), b(b), c(c) {};

    Line(const Point &, const Point &);

    Line(const Point &, const Vector &);

    double get_a() { return this->a; };

    double get_b() { return this->b; };

    double get_c() { return this->c; };

    Vector get_vector();

    Point get_point();

    void shift(const Vector &);

    bool contains_point(const Point &) const;

    bool cross_segment(const Segment &) const;

    bool cross_line(const Line &) const;

    Point cross_point(const Line &) const;

};

class Ray : public Figure {
private:
    Vector a;
    Point beginning;
public:
    Ray(const Vector &a, const Point &b) : a(a), beginning(b) {};

    Ray(const Point &a, const Point &b) : a(Vector(a, b)), beginning(a) {};

    void shift(const Vector &);

    bool contains_point(const Point &) const;

    bool cross_segment(const Segment &) const;
};

#endif //HOMEWORK_GEOMETRY_H
