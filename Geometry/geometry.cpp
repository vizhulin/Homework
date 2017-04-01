//
// Created by Artyom on 01.04.2017.
//

#include "geometry.h"
#include <iostream>
#include <cstdlib>
#include <iostream>
#include <cmath>

using namespace std;

double abs(const Vector &a) {
    return sqrt(a.x * a.x + a.y * a.y);
}

istream &operator>>(istream &in, Vector &a) {
    in >> a.x >> a.y;
    return in;
}

ostream &operator<<(ostream &out, const Vector &a) {
    cout << a.x << " " << a.y;
    return out;
}

Vector Vector::operator+(const Vector &a) {
    Vector res;
    res.x = this->x + a.x;
    res.y = this->y + a.y;
    return res;
}

Vector Vector::operator-(const Vector &a) {
    Vector res;
    res.x = this->x - a.x;
    res.y = this->y - a.y;
    return res;
}

double Vector::operator*(const Vector &a) {
    return (this->x * a.x + this->y * a.y);
}

double vector_product(const Vector &a, const Vector &b) {
    return b.x * a.y - b.y * a.x;
}

Vector::Vector(const Point &a, const Point &b) {
    this->x = b.get_x() - a.get_x();
    this->y = b.get_y() - a.get_y();
}

Point &Point::operator=(const Point &a) {
    this->x = a.x;
    this->y = a.y;
    return *this;
}

istream &operator>>(std::istream &in, Point &a) {
    in >> a.x >> a.y;
    return in;
}

ostream &operator<<(ostream &out, const Point &a) {
    out << a.x << " " << a.y;
    return out;
}

void Point::shift(const Vector &a) {
    this->x += a.get_x();
    this->y += a.get_y();
}

bool Point::contains_point(const Point &a) const {
    if (this->x == a.get_x() && this->y == a.get_y())
        return true;
    else
        return false;
}

bool Point::cross_segment(const Segment &s) const {
    Vector a(s.get_begining(), s.get_end());
    Vector b(*this, s.get_begining());
    Vector c(*this, s.get_end());
    return vector_product(a, b) == 0 && b * c < 0;
}

void Segment::shift(const Vector &a) {
    this->begining.shift(a);
    this->end.shift(a);
}

bool Segment::contains_point(const Point &a) const {
    return a.cross_segment(*this);
}

bool Segment::cross_segment(const Segment &s) const {
    if (s.contains_point(this->begining) || s.contains_point(this->end) || this->contains_point(s.get_begining()) ||
        this->contains_point(s.get_end()))
        return true;
    else {
        Vector a(this->begining, this->end);
        Vector b(this->begining, s.begining);
        Vector c(this->begining, s.end);
        return vector_product(a, b) * vector_product(a, c) < 0;
    }
}

Line::Line(const Point &a, const Point &b) {
    this->a = b.get_y() - a.get_y();
    this->b = a.get_x() - b.get_x();
    this->c = a.get_y() * b.get_x() - a.get_x() * b.get_y();
}

Line::Line(const Point &b, const Vector &a) {
    this->a = -a.get_y();
    this->b = a.get_x();
    this->c = a.get_y() * b.get_x() - a.get_y() * b.get_y();
}

Vector Line::get_vector() {
    return Vector(-this->b, this->a);
}

Point Line::get_point() {
    if (a != 0)
        return Point(-c / a, 0);
    else
        return Point(0, -c / b);
}

void Line::shift(const Vector &a) {
    this->c += this->a * a.get_x() + this->b * a.get_y();
}

bool Line::contains_point(const Point &a) const {
    return this->a * a.get_x() + this->b * a.get_y() + this->c == 0;
}

bool Line::cross_segment(const Segment &a) const {
    return (this->a * a.get_begining().get_x() + this->b * a.get_begining().get_y() + this->c) *
           (this->a * a.get_end().get_x() + this->b * a.get_end().get_y() + this->c) <= 0;
}

Point Line::cross_point(const Line &line) const {
    double d = this->a * this->b - line.a * line.b;
    double x = -(this->c * this->b - line.c * line.b) / d;
    double y = -(this->a * this->c - line.a * line.c) / d;
    return Point(x, y);
}

bool Line::cross_line(const Line &line) const {
    double d = (this->a * this->b - line.a * line.b);
    return d >= 0;
}


void Ray::shift(const Vector &a) {
    this->beginning.shift(a);
}

bool Ray::contains_point(const Point &c) const {
    Vector b(c, this->beginning);
    return (vector_product(this->a, b) == 0 && b * this->a >= 0);
}

bool Ray::cross_segment(const Segment &s) const {
    Line line1(this->beginning, this->a);
    Line line2(s.get_begining(), s.get_end());
    if (line1.cross_line(line2)) {
        Point p = line1.cross_point(line2);
        return s.contains_point(p) && this->contains_point(p);
    } else
        return false;
}