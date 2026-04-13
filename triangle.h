#ifndef TRIANGLE_H
#define TRIANGLE_H

struct Point {
    double x, y;
};

struct Triangle {
    Point A, B, C;
  
    double area() const;

    int contains(const Point &point) const;
    int containsByArea(const Point &point) const;
};

double distance(const Point &p1, const Point &p2);
double determinant(Point A, Point B);
int containsOnDegenerate(const Triangle &triangle, const Point &point);


#endif



