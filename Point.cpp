#include "Point.h"
#include <cmath>
#include <string>
#include <cstdlib>



namespace Clustering {

    // Constructor
    // Initializes the point to 0
    Point::Point(int dimension) {
        dim = dimension;
        values = new double[dimension];
        for (int i = 0; i < dimension; i++) {
            values[i] = 0;
        }
    }

// Constructor
// Initializes the point to the values in an array
    Point::Point(int dimension, double *coordinates) {
        dim = dimension;
        values = new double[dimension];
        for (int i = 0; i < dimension; i++) {
            values[i] = coordinates[i];
        }
    }

    //copy constructor
    Point::Point(const Point &copyPt) {
        dim = copyPt.dim;
        values = new double[dim];
        for (int i = 0; i < dim; i++) {
            values[i] = copyPt.values[i];
        }
    }

    void Point::operator=(const Point &copyPt) {
        if (this == &copyPt) {
            return;
        }
        dim = copyPt.dim;
        delete[] values;
        values = new double[dim];
        for (int i = 0; i < dim; i++) {
            values[i] = copyPt.values[i];
        }
    }

// Destructor
// No dynamic allocation, so nothing to do; if omitted, generated automatically
    Point::~Point() {
        delete[] values;
    }

// Mutator methods
// Change the values of private member variables

    void Point::setValue(int dimension, double newValue) {
        values[dimension - 1] = newValue;
    }


// Accessors
// Return the current values of private member variables

    double Point::getValue(int dimension) {
        return values[dimension - 1];
    }

    int Point::getDim() {
        return dim;
    }


// returns the distance from another specified point
    double Point::distanceTo(const Point &otherPoint) {
        double sum = 0;
        double valueDistance;
        for (int i = 0; i < dim; i++) {
            valueDistance = (values[i] - otherPoint.values[i]);
            sum += (valueDistance * valueDistance);
        }
        return sqrt(sum);
    }

//Overload operators
   bool operator==(const Point& lhs, const Point &rhs) {

        for (int i = 0; i < lhs.dim; i++) {
            if (lhs.values[i] != rhs.values[i])
                return false;
        }
        return true;
    }

    bool operator!=(const Point& lhs, const Point &rhs) {
        if (lhs == rhs)
            return false;
        return true;
    }

    bool operator<=(const Point& lhs, const Point &rhs) {

        for (int i = 0; i < lhs.dim; i++) {
            if (lhs.values[i] > rhs.values[i])
                return false;
        }
        return true;
    }

    bool operator>=(const Point& lhs, const Point &rhs) {

        for (int i = 0; i < lhs.dim; i++) {
            if (lhs.values[i] < rhs.values[i])
                return false;
        }
        return true;
    }

    bool operator<(const Point& lhs, const Point &rhs) {
        if (lhs >= rhs)
            return false;
        return true;
    }

    bool operator>(const Point& lhs, const Point &rhs) {
        if (lhs <= rhs)
            return false;
        return true;
    }

    const Point operator+(const Point& lhs, const Point &rhs) {
        Point temp(lhs.dim);
        for (int i = 0; i < rhs.dim; i++) {
            temp.values[i] = lhs.values[i] + rhs.values[i];
        }
        return temp;
    }

    const Point operator-(const Point& lhs, const Point &rhs) {
        Point temp(lhs.dim);
        for (int i = 0; i < rhs.dim; i++) {
            temp.values[i] = lhs.values[i] - rhs.values[i];
        }
        return temp;
    }

    const Point Point::operator*(double rhs)const {
        Point temp(dim);
        for (int i = 0; i < dim; i++) {
            temp.values[i] = values[i] * rhs;
        }
        return temp;
    }

    const Point Point::operator/(double rhs)const {
        Point temp(dim);
        for (int i = 0; i < dim; i++) {
            temp.values[i] = values[i] / rhs;
        }
        return temp;
    }

    Point operator+=(Point& lhs, const Point &rhs) {
        for (int i = 0; i < lhs.dim; i++) {
            lhs.values[i] += rhs.values[i];
        }
        return lhs;
    }

    Point operator-=(Point& lhs, const Point &rhs) {
        for (int i = 0; i < lhs.dim; i++) {
            lhs.values[i] -= rhs.values[i];
        }
        return lhs;
    }

    Point Point::operator/=(double rhs) {
        for (int i = 0; i < dim; i++) {
            values[i] /= rhs;
        }
        return *this;
    }

    Point Point::operator*=(double rhs) {
        for (int i = 0; i < dim; i++) {
            values[i] *= rhs;
        }
        return *this;
    }

    std::ostream &operator<<(std::ostream &os, const Point &output) {

        for (int i = 0; i < output.dim; i++) {
            os << output.values[i];
            if(i < output.dim - 1)
                os << ", ";
        }
        std::cout << ": ";

        return os;
    }

    std::istream &operator>>(std::istream &os, Point &input) {
        std::string value;
        double d;

        int i = 1;
        while (getline(os, value, ',')) {

            double resultDouble;//number which will contain the result
            std::stringstream convert(value); // stringstream used for the conversion initialized with the contents of Text

            if ( !(convert >> resultDouble) )//give the value to Result using the characters in the string
                resultDouble = 0;//if that fails set Result to 0

            input.setValue(i++, resultDouble);
        }

//        std::cout << "Input coordinates: " << std::endl;
//        for (int i = 0; i < input.dim; i++) {
//            os >> input.values[i];
//        }

        return os;
    }
}
