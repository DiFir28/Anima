#pragma once

#include "config.h"

class Point {
public:
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}
    
    Point operator + (Point p)const{
        Point result (this->x + p.x,this->y + p.y);
        return result;
    }
    
    Point operator - (Point p)const{
        Point result (this->x - p.x,this->y - p.y);
        return result;
    }
    
    Point& operator += (Point p)noexcept{
        x += p.x;
        y += p.y;
        return *this;
    }
    
    Point& operator -= (Point p)noexcept{
        x -= p.x;
        y -= p.y;
        return *this;
    }
    
    bool operator ==( const Point& p) {
        return ((x == p.x) * (y == p.y));
    }
};

Point point(int x, int y){
    return Point(x,y);
}

typedef float rad;  

class Vec{
    public:

    Point beg = point(0,0), end = point(0,0);

    Vec(Point beg = point(0,0), Point end = point(0,0)) : beg(beg), end(end){}

    
    rad ang;
    float len;
    
    
    int dx(){return (end.x-beg.x);}
    int dy(){return (end.y-beg.x);}

    Point dxy(){
        Point result(dx(), dy());
        return result;
    }
    
    void calcang(){
        len = sqrt(dx()*dx() + dy()*dy());
        ang = atan2(dy(), dx());
    } 

    void calcxy(){
        end.x = beg.x + len*cos(ang*M_PI);
        end.y = beg.y + len*sin(ang*M_PI );
    }
    
    Vec rot(rad dang)const{
        Vec result = *this;
        result.ang+=dang;
        result.calcxy();
        return result;
    }
    
    Vec elon(rad dlen)const{
        Vec result = *this;
        result.len+=dlen;
        result.calcxy();
        return result;
    }
    
    Vec operator+(Vec& v1) const {
    Vec result;
    result.beg = this->beg; 
    result.end = point(this->end.x + v1.dx(), this->end.y + v1.dy()); 
    result.calcang();
    return result; 
}
    Vec operator-(Vec& v1) const {
    Vec result;
    result.beg = this->beg; 
    result.end = point(this->end.x - v1.dx(), this->end.y - v1.dy()); 
    result.calcang();
    return result;}
    
    int operator*(Vec v1){
        return dx()*v1.dx()+dy()*v1.dy();
    }

    
};

Vec vec(Point beg = point(0,0), Point end = point(0,0)){
    return Vec(beg, end);
}

Vec vec(Point end = point(0,0)){
    return Vec(point(0,0), end);
}

// 