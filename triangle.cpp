#include <iostream>
#include <cmath>
#include "triangle.h"

using namespace std;

#define INSIDE 1
#define OUTSIDE -1
#define BORDER 0

int sign(double n) {
    if(fabs(n) < 1e-9) return 0;
    if (n > 0) return 1;
    else return -1;
}

double distance(const Point &p1, const Point &p2) {
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}

double determinant(Point A, Point B){
    return A.x * B.y - A.y * B.x;
}

double Triangle::area() const {
    return 0.5 * fabs(determinant(A, B) + determinant(B, C) + determinant(C, A));
}

int containsOnDegenerate(const Triangle &triangle, const Point &point){
    Point p1 = triangle.A;
    Point p2 = triangle.B;
    double maxDist = distance(p1, p2);
    
    if(maxDist < distance(triangle.A, triangle.C)){
        p2 = triangle.C;
        maxDist = distance(triangle.A, triangle.C);
    }
    if(maxDist < distance(triangle.B, triangle.C)){
        p1 = triangle.B;
        p2 = triangle.C;
        maxDist = distance(triangle.B, triangle.C);
    }
    
    if (distance(point, p1) + distance(point, p2) - distance(p1, p2) < 1e-9)
        return BORDER;
    else
        return OUTSIDE;
}

int Triangle::containsByArea(const Point &point) const {
    if (area() == 0) {
        return containsOnDegenerate(*this, point);
    }

    double s1 = Triangle{A, B, point}.area();
    double s2 = Triangle{B, C, point}.area();
    double s3 = Triangle{A, C, point}.area();

    double s = area();

    if (s == (s1 + s2 + s3)) {

        if (s1 == 0 || s2 == 0 || s3 == 0) {
            return BORDER;
        }

        return INSIDE;
    }

    return OUTSIDE;
}

int Triangle::contains(const Point &point) const {

    const Point AP{point.x - A.x, point.y - A.y};
    const Point BP{point.x - B.x, point.y - B.y};
    const Point CP{point.x - C.x, point.y - C.y};
    const Point AB{B.x - A.x, B.y - A.y};
    const Point BC{C.x - B.x, C.y - B.y};
    const Point CA{A.x - C.x, A.y - C.y};

    const double sign1 = sign(determinant(AP, AB));
    const double sign2 = sign(determinant(BP, BC));
    const double sign3 = sign(determinant(CP, CA));

    if(area() == 0){
        return containsOnDegenerate(*this, point);
    }

    if(sign1 == sign2 && sign2 == sign3){
        return INSIDE;
    }

    if ((sign1 == 0 && sign2 == sign3) || (sign2 == 0 && sign1 == sign3) ||
     (sign3 == 0 && sign1 == sign2) || (sign1 == 0 && sign2 == 0) || 
     (sign1 == 0 && sign3 == 0) || (sign2 == 0 && sign3 == 0)) {
        return BORDER;
    }
    else return OUTSIDE;
}

void result() {
    Triangle triangle;
    cout << "Введіть координати вершини A (x1, y1): ";
    cin >> triangle.A.x >> triangle.A.y;

    cout << "Введіть координати вершини B (x2, y2): ";
    cin >> triangle.B.x >> triangle.B.y;

    cout << "Введіть координати вершини C (x3, y3): ";
    cin >> triangle.C.x >> triangle.C.y;

    if(triangle.area() == 0){
        cout << "Трикутник вироджений" << endl;
    }
    else {
        cout << "Трикутник не вироджений" << endl;
    }
    cout << "Введіть кількість точок для перевірки на належність трикутнику: ";
    int n;
    cin >> n;
    cout << endl;

    for(int i = 0; i < n; i++){
        Point point;
        cout << "Введіть координати точки (x, y): ";
        cin >> point.x;
        cin >> point.y;
        int result = triangle.contains(point);
        if(result == INSIDE){
            cout << "За методом векторного добутку: точка належить трикутнику" << endl;
        } else if(result == BORDER){
            cout << "За методом векторного добутку: точка належить границі трикутника" << endl;
        } else {
            cout << "За методом векторного добутку: точка не належить трикутнику" << endl;
        }
        result = triangle.containsByArea(point);
        if(result == INSIDE){
            cout << "За методом площ: точка належить трикутнику" << endl;
        } else if(result == BORDER){
            cout << "За методом площ: точка належить границі трикутника" << endl;
        } else {
            cout << "За методом площ: точка не належить трикутнику" << endl;
        }
        cout << endl;
    }

    return;
 }