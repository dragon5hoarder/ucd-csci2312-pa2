// A n-dimensional point class!
// Coordinates are double-precision floating point.

#ifndef __point_h
#define __point_h

#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>
#include <string>
#include <cstdlib>

#include "Exceptions.h"

namespace Clustering {
    template<typename T, int dim>
    class Point {

    private:

        static unsigned int pointID;
        unsigned int thisID;
        std::vector<T> values;

    public:
        // Constructors
        Point();

        Point(T *coordinates);

        //copy constructor and assignment operator
        Point(const Point &copyPt);

        void operator=(const Point &copyPt);

        // Destructor
        ~Point();

        // Mutator method
        void setValue(int dimension, T newValue);

        // Accessor method
        T getValue(int dimension);

        // int getDim();
        unsigned int getId() const { return thisID; }

        // finds the distance from another point
        T distanceTo(const Point &otherPoint);

        // overloaded operators
        template<typename S, int dim2>
        friend bool operator==(const Point<S, dim2> &lhs, const Point<S, dim2> &rhs);

        template<typename S, int dim2>
        friend bool operator!=(const Point<S, dim2> &lhs, const Point<S, dim2> &rhs);

        template<typename S, int dim2>
        friend bool operator<=(const Point<S, dim2> &lhs, const Point<S, dim2> &rhs);

        template<typename S, int dim2>
        friend bool operator>=(const Point<S, dim2> &lhs, const Point<S, dim2> &rhs);

        template<typename S, int dim2>
        friend bool operator<(const Point<S, dim2> &lhs, const Point<S, dim2> &rhs);

        template<typename S, int dim2>
        friend bool operator>(const Point<S, dim2> &lhs, const Point<S, dim2> &rhs);

        template<typename S, int dim2>
        friend const Point<S, dim2> operator+(const Point<S, dim2> &lhs, const Point<S, dim2> &rhs);

        template<typename S, int dim2>
        friend const Point<S, dim2> operator-(const Point<S, dim2> &lhs, const Point<S, dim2> &rhs);

        const Point operator*(T rhs) const;

        const Point operator/(T rhs) const;

        template<typename S, int dim2>
        friend Point operator+=(Point<S, dim2> &lhs, const Point<S, dim2> &rhs);

        template<typename S, int dim2>
        friend Point operator-=(Point<S, dim2> &lhs, const Point<S, dim2> &rhs);

        Point operator*=(T rhs);

        Point operator/=(T rhs);

        T &operator[](int index) {
            try {
                if (index >= dim)
                    throw OutOfBoundsEx(0);
                return values[index - 1];
            } catch (OutOfBoundsEx &ex) {
                std::cerr << ex << std::endl;

            }
        }

        //IO
        template<typename S, int dim2>
        friend std::ostream &operator<<(std::ostream &os, const Point<S, dim2> &output);

        template <typename S, int dim2>
        friend std::istream &operator>>(std::istream &os, Point<S, dim2> &input);


    };






}


#include "Point.cpp"
#endif // __point_h

