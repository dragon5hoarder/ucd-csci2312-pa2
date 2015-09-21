#include <iostream>
#include "Point.h"

using namespace std;
using namespace Clustering;

int main() {
    cout << "Hello, World!" << endl;
//Testing

    double *array2 = new double[3];
    for (int i = 0; i < 3; i++)
        array2[i] = 1;

    Point p1(3);
    Point p2(3, array2), p3(p1), p4(3);
    p4 = p2;

    cout << "Dimensions: " << p1.getDim() << endl;

    cout << p1 << p2;
    cout << p1.distanceTo(p2) << endl;

    if (p1 == p2) {
        cout << "points are equal" << endl;
    }
    if (p1 != p2) {
        cout << "points are different" << endl;
    }

    Point p5(3);
    p5 = p2 + p4;
    Point p6 = p2 * 2;
    cout << p5 << p6;

    p5 += p2;
    p6 *= 6;
    cout << p5 << p6;

    if (p1 <= p2) {
        cout << "p1 < p2" << endl;
    }
    if (p5 >= p2) {
        cout << "p5 > p2" << endl;
    }

    cout << p5[2] << endl;

    delete [] array2;
    return 0;
}