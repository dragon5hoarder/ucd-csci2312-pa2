#include <iostream>
#include "Point.h"

using namespace std;
//using namespace Clustering;

int main() {
    cout << "Hello, World!" << endl;
//Testing

    double *array2 = new double[3];
    for (int i = 0; i < 3; i++)
        array2[i] = 1;

    Point p1(3);
    Point p2(3, array2), p3(p1), p4(3);
    p4 = p1;



    for (int i = 1; i <= 3; i++){
        cout << p1.getValue(i) << endl;
        cout << p2.getValue(i) << endl;
        cout << p3.getValue(i) << endl;
        cout << p4.getValue(i) << endl;
    }
    cout << p1.distanceTo(p2) << endl;

    delete [] array2;
    return 0;
}