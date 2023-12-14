#pragma once
#include <iostream>
#include <cmath>
#include <fstream>


using namespace std;

class Point {
private:
    double x, y;

public:
    Point() = default;
    Point(double trux, double truy) : x(trux), y(truy){}
    Point(const Point& p);

    double getX() const;
    double getY() const;

    Point operator=(const Point& p);
};

class Circle {
private:
    double radius;
    Point center;

public:
    Circle() = default;
    Circle(const Point& c, double r);
    Circle(const Circle& other);

    double getRadius();
    Point getCenter();

    Circle operator=(const Circle& p);

    void findIntersection(const Circle& other, Point& intersection1 /*Point& intersection2*/) const;
};

class Triangle {
private:
    double AB;
    double BC;
    double AC;
    Point A, B, C;

public:
    Triangle() = default;
    void set_Triangle(double nAB, double nBC, double nAC);

    Point getA();
    Point getB();
    Point getC();

    void print_Triangle(const string& filename) const;
    bool read_Triangle(const string& namefile);
    bool is_Triangle(double AB, double BC, double AC);
};