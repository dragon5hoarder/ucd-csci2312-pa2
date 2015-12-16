//
// Created by dragon5hoarder on 11/15/2015.
//

#include "Exceptions.h"

namespace Clustering {
    DimensionalityMismatchEx::DimensionalityMismatchEx(int num){
        name = "DimensionalityMismatchEx";
        errorNum = num;
    }

    std::ostream &operator<<(std::ostream &os, const DimensionalityMismatchEx &output){
        os << output.name << " " << output.errorNum << ": ";
        if(output.errorNum == 2)
            os << "unable to compare two points with different dimensions";
        else if (output.errorNum == 0)
            os << "unable to assign a point to a point with different dimensions";
        else if (output.errorNum == 1)
            os << "unable use arithmetic on two points with different dimensions";
        else if (output.errorNum == 3)
            os << "point does not match dimension of cluster";
        return os;
    }

    OutOfBoundsEx::OutOfBoundsEx(int num){
        name = "OutOfBoundsEx";
        errorNum = num;
    }

    std::ostream &operator<<(std::ostream &os, const OutOfBoundsEx &output){
        os << output.name << " " << output.errorNum << ": ";
        if(output.errorNum == 0)
            os << "Point index is out of bounds";
        if(output.errorNum == 1)
            os << "Cluster index is out of bounds";

        return os;
    }

    RemoveFromEmptyEx::RemoveFromEmptyEx(int num){
        name = "RemoveFromEmptyEx";
        errorNum = num;
    }

    std::ostream &operator<<(std::ostream &os, const RemoveFromEmptyEx &output){
        os << output.name << " " << output.errorNum << ": ";
        if(output.errorNum == 0)
            os << "unable to remove Point from empty Cluster";
        if(output.errorNum == 1)
            os << "unable to compute Centroid in an empty Cluster";

        return os;
    }
}
