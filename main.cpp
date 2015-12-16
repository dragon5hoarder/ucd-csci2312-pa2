#include <iostream>
#include <fstream>

#include "Point.h"
#include "Cluster.h"
#include "KMeans.h"


using namespace std;
using namespace Clustering;

int main() {
    cout << "Hello, World!" << endl;
//Testing
//   ifstream file("points.txt");

//    KMeans<3, 5> test(file);

//    file.close();
//    const int dim = 5;
//    Point<double, dim> p1();
//    cout << p1;


//    Cluster c1;

//    cout << "c1: " << endl;
//    file >> c1;
//    cout << c1;
//    file.close();

//
//    cout << c1;
//    c1.computeCent();
//    cout << c1.getCent() << endl;
//    cout << c1.intraClusterDistance() << endl;
//
//
//
//    std::ifstream file2("points.txt");
//    Cluster c2;
//
//    cout << "c2: " << endl;
//    file2 >> c2;
//    file2.close();
//
//    cout << c2;




//    double *array2 = new double[3];
//    for (int i = 0; i < 3; i++)
//        array2[i] = 1;
//
//    Point<double, 4> p1();
//    Point p2(3, array2), p3(p1), p4(3);
//    p4 = p2;
//
//    cout << "Dimensions of p1: " << p1.getDim() << endl;
//
//    cout<< "p1 and p2:" << endl;
//   cout << p1;
//    cout << p1.distanceTo(p2) << endl;
//
//    if (p1 == p2) {
//        cout << "p1 and p2 are equal" << endl;
//    }
//    if (p1 != p2) {
//        cout << "p1 and p2 are different" << endl;
//    }
//
//    std::ifstream file("points.txt");
//
//    //cout << "p2: ";
//    //file >> p2;
//
//    file.close();
//
//
//    Point p5(3);
//    p5 = p2 + p4;
//    Point p6 = p2 * 2;
//    cout << "points p5 and p6:" << endl;
//    cout << p5 << p6;
//
//    p5 += p2;
//    p6 *= 6;
//    cout << "points p5 and p6:" << endl;
//    cout << p5 << p6;
//
//
//    if (p1 <= p2) {
//        cout << "p1 < p2" << endl;
//    }
//    if (p5 >= p2) {
//        cout << "p5 > p2" << endl;
//    }
//
//    cout << "point p5's 2nd dimension:" << endl;
//    cout << p5[2] << endl;
//
//    Cluster c1;
//    c1.add(&p1);
//    c1.add(&p2);
//    c1.add(&p3);
//    c1.add(&p6);
//    c1.add(&p5);
//
//    cout << "Cluster c1 " << endl;
//    cout << c1;
//
//    cout << "Cluster c1 ";
//    c1.remove(&p6);
//    cout << c1;
//
//    cout << "Cluster c2 and c3 ";
//    Cluster c2(c1);
//    cout << c2;
//    Cluster c3;
//    c3 = c1;
//    cout << c3;
//
//
//    double *array1 = new double[3];
//    for (int i = 0; i < 3; i++)
//        array1[i] = i;
//
//    Point p7(3, array1);
//
//
//
//    Cluster c4;
//    c4.add(&p4);
//    c4.add(&p2);
//    c4.add(&p3);
//    c4.add(&p6);
//    c4.add(&p7);
//
//    cout << "Cluster c4 ";
//    cout << c4;
//
//    c4 += p1;
//    cout << "added p1 to c4 " << endl;
//    cout << c4;
//
//    c4 -= p1;
//    cout << "removed p1 from c4 " << endl;
//    cout << c4;
//
//    cout << "union of c1 and c4 ";
//    c1 += c4;
//    cout << c1;
//
//    cout << "difference of c1 and c4 ";
//    c1 -= c4;
//    cout << c1;
//
//    cout << "c5: ";
//    Cluster c5 = c2;
//    cin >> c5;
//    cout << c5;
//
//
//
//    delete [] array1;
//    delete [] array2;
    return 0;
}