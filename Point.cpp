
#include <cmath>
#include <string>
#include <cstdlib>

//#include "Point.h"



namespace Clustering {

    template <typename T, int dim>
    unsigned int Point<T, dim>::pointID = 0;


    // Constructor
    // Initializes the point to 0
    template <typename T, int dim>
    Point<T, dim>::Point() {
        //dim = dimension;
        //std::cout << thisID << ": " << values.size() << std::endl;
        for (int i = 0; i < dim; i++) {
            values.push_back(0);
        }
        thisID = pointID++;
    }

// Constructor
// Initializes the point to the values in an array
    template <typename T, int dim>
    Point<T, dim>::Point(T *coordinates) {
        //dim = dimension;
        for (int i = 0; i < dim; i++) {
            values.push_back(coordinates[i]);
        }
        thisID = pointID++;
    }

    //copy constructor
    template <typename T, int dim>
    Point<T, dim>::Point(const Point &copyPt) {
        //dim = copyPt.dim;
        auto it = copyPt.values.begin();
        for (int i = 0; i < dim; i++) {
            values.push_back(it[i]);
        }
        thisID = copyPt.thisID;
    }

    template <typename T, int dim>
    void Point<T, dim>::operator=(const Point &copyPt) {
        if (this == &copyPt) {
            return;
        }
        //dim = copyPt.dim;
        values.erase(values.begin(),values.end());
        for (int i = 0; i < dim; i++) {
            values.push_back(copyPt.values[i]);
        }
        thisID = copyPt.thisID;
    }

// Destructor
// No dynamic allocation, so nothing to do; if omitted, generated automatically
    template <typename T, int dim>
    Point<T, dim>::~Point() {
        //values.erase(values.begin());
    }

// Mutator methods
// Change the values of private member variables

    template <typename T, int dim>
    void Point<T, dim>::setValue(int dimension, T newValue) {
        values[dimension - 1] = newValue;
    }


// Accessors
// Return the current values of private member variables

    template <typename T, int dim>
    T Point<T, dim>::getValue(int dimension) {
        return values[dimension - 1];
    }

//    int Point::getDim() {
//        return dim;
//    }


// returns the distance from another specified point
    template <typename T, int dim>
    T Point<T, dim>::distanceTo(const Point &otherPoint) {
        T sum = 0;
        T valueDistance;
        for (int i = 0; i < dim; i++) {
            valueDistance = (values[i] - otherPoint.values[i]);
            sum += (valueDistance * valueDistance);
        }
        return sqrt(sum);
    }

//Overload operators

    template <typename W, int dim3>
    bool operator==(const Point<W, dim3>& lhs, const Point<W, dim3> &rhs) {
//        if (lhs.dim != rhs.dim)
//            throw DimensionalityMismatchEx(2);
        if(lhs.thisID != rhs.thisID) {
//        for (int i = 0; i < lhs.dim; i++) {
//            if (lhs.values[i] != rhs.values[i])
                return false;
        }
        //}
        return true;
    }

    template <typename W, int dim3>
    bool operator!=(const Point<W, dim3>& lhs, const Point<W, dim3>& rhs) {
        if (lhs == rhs)
            return false;
        return true;
    }

    template <typename W, int dim3>
    bool operator<=(const Point<W, dim3>& lhs, const Point<W, dim3> &rhs) {
//        if (lhs.dim != rhs.dim)
//            throw DimensionalityMismatchEx(2);

        for (int i = 0; i < dim3; i++) {
            if (lhs.values[i] > rhs.values[i])
                return false;
        }
        return true;
    }

    template <typename W, int dim3>
    bool operator>=(const Point<W, dim3>& lhs, const Point<W, dim3> &rhs) {
//        if (lhs.dim != rhs.dim)
//            throw DimensionalityMismatchEx(2);
        for (int i = 0; i < dim3; i++) {
            if (lhs.values[i] < rhs.values[i])
                return false;
        }
        return true;
    }

    template <typename W, int dim3>
    bool operator<(const Point<W, dim3>& lhs, const Point<W, dim3> &rhs) {
        if (lhs >= rhs)
            return false;
        return true;
    }

    template <typename W, int dim3>
    bool operator>(const Point<W, dim3>& lhs, const Point<W, dim3> &rhs) {
        if (lhs <= rhs)
            return false;
        return true;
    }

    template <typename W, int dim3>
    const Point<W, dim3> operator+(const Point<W, dim3>& lhs, const Point<W, dim3> &rhs) {

//        if (lhs.dim != rhs.dim)
//            throw DimensionalityMismatchEx(1);
        Point<W, dim3> temp();
        for (int i = 0; i < dim3; i++) {
            temp.values[i] = lhs.values[i] + rhs.values[i];
        }
        return temp;
    }

    template <typename W, int dim3>
    const Point<W, dim3> operator-(const Point<W, dim3>& lhs, const Point<W, dim3> &rhs) {

//        if (lhs.dim != rhs.dim)
//            throw DimensionalityMismatchEx(1);
        Point<W, dim3> temp();
        for (int i = 0; i < dim3; i++) {
            temp.values[i] = lhs.values[i] - rhs.values[i];
        }
        return temp;
    }

    template <typename T, int dim>
    const Point<T, dim> Point<T, dim>::operator*(T rhs)const {
        Point<T, dim> temp();
        for (int i = 0; i < dim; i++) {
            temp.values[i] = values[i] * rhs;
        }
        return temp;
    }

    template <typename T, int dim>
    const Point<T, dim> Point<T, dim>::operator/(T rhs)const {
        Point temp(*this);
        for (int i = 0; i < dim; i++) {
            temp.values[i] /= rhs;
        }
        return temp;
    }

    template <typename W, int dim3>
    Point<W, dim3> operator+=(Point<W, dim3>& lhs, const Point<W, dim3> &rhs) {
//        if (lhs.dim != rhs.dim)
//            throw DimensionalityMismatchEx(1);
        for (int i = 0; i < dim3; i++) {
            lhs.values[i] += rhs.values[i];
        }
        return lhs;
    }

    template <typename W, int dim3>
    Point<W, dim3> operator-=(Point<W, dim3>& lhs, const Point<W, dim3> &rhs) {
//        if (lhs.dim != rhs.dim)
//            throw DimensionalityMismatchEx(1);
        for (int i = 0; i < dim3; i++) {
            lhs.values[i] -= rhs.values[i];
        }
        return lhs;
    }

    template <typename T, int dim>
    Point<T, dim> Point<T, dim>::operator/=(T rhs) {
        for (int i = 0; i < dim; i++) {
            values[i] /= rhs;
        }
        return *this;
    }

    template <typename T, int dim>
    Point<T, dim> Point<T, dim>::operator*=(T rhs) {
        for (int i = 0; i < dim; i++) {
            values[i] *= rhs;
        }
        return *this;
    }

    template <typename W, int dim3>
    std::ostream &operator<<(std::ostream &os, const Point<W, dim3> &output) {

        for (int i = 0; i < dim3; i++) {
            os << output.values[i];
            if(i < dim3 - 1)
                os << ", ";
        }
        os << ": ";

        return os;
    }

    template <typename W, int dim3>
    std::istream &operator>>(std::istream &os, Point<W, dim3> &input) {
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

        std::cout << "Input coordinates: " << std::endl;
        for (int i = 0; i < input.dim; i++) {
            os >> input.values[i];
        }

        return os;
    }

}
