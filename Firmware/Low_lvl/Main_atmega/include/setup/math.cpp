#pragma once

#include "config.h"

template <typename T>
T sign(T a)
{
    return (a > 0) * 2 - 1;
}

float between(float first_angle, float second_angle)
{    
    float output = ((second_angle - first_angle));
    output -= round(output / (M_PI * 2)) * 2 * M_PI;
    return output;
}

class Point
{
public:
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}

    Point operator+(Point p) const
    {
        Point result(this->x + p.x, this->y + p.y);
        return result;
    }

    Point operator-(Point p) const
    {
        Point result(this->x - p.x, this->y - p.y);
        return result;
    }

    Point &operator+=(Point p) noexcept
    {
        x += p.x;
        y += p.y;
        return *this;
    }

    Point &operator-=(Point p) noexcept
    {
        x -= p.x;
        y -= p.y;
        return *this;
    }

    // bool operator ==( const Point& p) {
    //     return ((x == p.x) * (y == p.y));
    // }
};

Point point(int x, int y)
{
    return Point(x, y);
}


class Vec
{
public:
    Point beg = point(0, 0), end = point(0, 0);

    Vec(Point beg = point(0, 0), Point end = point(0, 0)) : beg(beg), end(end) {void calcang();}

    float ang = 0;
    float len = 1;

    int dx() { return (end.x - beg.x); }
    int dy() { return (end.y - beg.x); }

    Point dxy()
    {
        Point result(dx(), dy());
        return result;
    }

    void calcang()
    {
        len = sqrt(dx() * dx() + dy() * dy());
        ang = atan2(dy(), dx());
    }

    void calcxy()
    {
        end.x = beg.x + len * cos(ang * M_PI);
        end.y = beg.y + len * sin(ang * M_PI);
    }

    Vec rot(float dang) const
    {
        Vec result = *this;
        result.ang += dang;
        result.calcxy();
        return result;
    }

    Vec elon(float dlen) const
    {
        Vec result = *this;
        result.len += dlen;
        result.calcxy();
        return result;
    }

    Vec operator+(Vec &v1) const
    {
        Vec result;
        result.beg = this->beg;
        result.end = point(this->end.x + v1.dx(), this->end.y + v1.dy());
        result.calcang();
        return result;
    }
    Vec operator-(Vec &v1) const
    {
        Vec result;
        result.beg = this->beg;
        result.end = point(this->end.x - v1.dx(), this->end.y - v1.dy());
        result.calcang();
        return result;
    }

    int operator*(Vec v1)
    {
        return dx() * v1.dx() + dy() * v1.dy();
    }
};

Vec vec(Point beg = point(0, 0), Point end = point(0, 0))
{
    return Vec(beg, end);
}

Vec vec(Point end = point(0, 0))
{
    return Vec(point(0, 0), end);
}

Vec radvec(float ang, float len)
{
    Vec result;
    result.ang = ang;
    result.len = len;
    return result;
}

Vec radvec(float ang)
{
    Vec result;
    result.ang = ang;
    return result;
}

//