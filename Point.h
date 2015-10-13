// A n-dimensional point class!
// Coordinates are double-precision floating point.

#ifndef __point_h
#define __point_h

#include <iostream>
#include <sstream>

namespace Clustering {
    class Point {

    private:
        int dim;
        double *values;

    public:
        // Constructors
        Point(int dimension);
        Point(int dimension, double *coordinates);

        //copy constructor and assignment operator
        Point(const Point& copyPt);
        void operator=(const Point& copyPt);

        // Destructor
        ~Point();

        // Mutator method
        void setValue(int dimension, double newValue);

        // Accessor method
        double getValue(int dimension);
        int getDim();

        // finds the distance from another point
        double distanceTo(const Point &otherPoint);

        // overloaded operators
        friend bool operator==(const Point& lhs, const Point& rhs);
        friend bool operator!=(const Point& lhs, const Point& rhs);
        friend bool operator<=(const Point& lhs, const Point& rhs);
        friend bool operator>=(const Point& lhs, const Point& rhs);
        friend bool operator<(const Point& lhs, const Point& rhs);
        friend bool operator>(const Point& lhs, const Point& rhs);
        friend const Point operator+(const Point& lhs, const Point& rhs);
        friend const Point operator-(const Point& lhs, const Point& rhs);
        const Point operator*(double rhs)const;
        const Point operator/(double rhs)const;

        friend Point operator+=(Point& lhs, const Point& rhs);
        friend Point operator-=(Point& lhs, const Point& rhs);
        Point operator*=(double rhs);
        Point operator/=(double rhs);

        double &operator[](int index) { return values[index - 1]; }

        friend std::ostream& operator<<(std::ostream& os, const Point& output);
        friend std::istream& operator>>(std::istream& os, Point& input);


    };

}

#endif // __point_h