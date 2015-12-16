//
// Created by dragon5hoarder on 11/15/2015.
//

#ifndef PA3_INT_EXCEPTIONS_H
#define PA3_INT_EXCEPTIONS_H

#include <string>
#include <iostream>

namespace Clustering {
    class DimensionalityMismatchEx{
    private:
        std::string name;
        int errorNum;
    public:
        DimensionalityMismatchEx(int num);
        std::string getName() { return name; }
        int getErr() { return errorNum; }
        friend std::ostream& operator<<(std::ostream& os, const DimensionalityMismatchEx& output);
    };

    class OutOfBoundsEx{
    private:
        std::string name;
        int errorNum;
    public:
        OutOfBoundsEx(int num);
        std::string getName() { return name; }
        int getErr() { return errorNum; }
        friend std::ostream& operator<<(std::ostream& os, const OutOfBoundsEx& output);
    };

    class RemoveFromEmptyEx{
    private:
        std::string name;
        int errorNum;
    public:
        RemoveFromEmptyEx(int num);
        std::string getName() { return name; }
        int getErr() { return errorNum; }
        friend std::ostream& operator<<(std::ostream& os, const RemoveFromEmptyEx& output);
    };
}

#endif //PA3_INT_EXCEPTIONS_H
