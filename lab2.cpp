 #include <iostream>
 #include "triangle.h"
 
 using namespace std;

#define INSIDE 1
#define OUTSIDE -1
#define BORDER 0
 
 int main() {
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

    return  0;
 }