//
// Created by dragon5hoarder on 9/19/2015.
//

#include "Cluster.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>


namespace Clustering {
    int Cluster::clustID = 0;

    Cluster::Cluster() {
        size = 0;
        points = nullptr;
        thisID = clustID++;
        pointDimension = 0;
        centroid = new Point(pointDimension);
        validCent = false;
    }

    Cluster::Cluster(const Cluster &copyCluster) {
        size = copyCluster.size;
        points = new Node;
        NodePtr tester = points;
        NodePtr copyTester = copyCluster.points;
        for (int i = 0; i < size; i++){
            tester->point = copyTester->point;
            tester->next = new Node;
            tester = tester->next;
            copyTester = copyTester->next;
        }
        tester->next = nullptr;
        thisID = clustID++;
        pointDimension = copyCluster.pointDimension;
        centroid = new Point(pointDimension);
        validCent = copyCluster.validCent;
    }

    void Cluster::operator=(const Cluster &copyCluster){
        if (this == &copyCluster) {
            return;
        }
        size = copyCluster.size;
        clear();
        points = new Node;
        NodePtr tester = points;
        NodePtr copyTester = copyCluster.points;
        for (int i = 0; i < size; i++){
            tester->point = copyTester->point;
            tester->next = new Node;
            tester = tester->next;
            copyTester = copyTester->next;
        }
        tester->next = nullptr;
        pointDimension = copyCluster.pointDimension;
        centroid = new Point(pointDimension);
        *centroid = *copyCluster.centroid;
        validCent = copyCluster.validCent;
    }

    Cluster::~Cluster(){
        clear();
        delete centroid;

    }

    void Cluster::clear(){
        if (points != nullptr) {
            NodePtr tester = points;
            tester = tester->next;
            NodePtr deleted = points;
            while (tester != nullptr) {
                delete deleted->point;
                delete deleted;
                deleted = tester;
                tester = tester->next;
            }
            delete deleted;
            points = nullptr;
        }
    }



    void Cluster::add(const PointPtr &addedPt) {

        NodePtr tester;
        NodePtr placeHolder = new Node;
        placeHolder->point = addedPt;
        bool statement = true;

        if (points == nullptr || *(points->point) >= *addedPt)

        {
            placeHolder->next = points;
            points = placeHolder;
            size++;
        }

        else
        {

            tester = points;

            while (tester->next!= nullptr && *(tester->next->point) < *addedPt)

            {
                tester = tester->next;
            }
            placeHolder->next = tester->next;
            tester->next = placeHolder;
            size++;
        }
        validCent = false;
    }

    const PointPtr& Cluster::remove(const PointPtr &deletedPt) {
        NodePtr tester;
        NodePtr deleted;

        if (points->point == deletedPt) {

            deleted = points;
            points = points->next;
            delete deleted;
            size--;
            return deletedPt;
        }

        else {
            for (NodePtr tester = points; tester != nullptr; tester = tester->next) {

                if (tester->next->point == deletedPt) {
                    deleted = tester->next;
                    if (tester->next->next == nullptr) {
                        tester->next = nullptr;
                    }
                    else {
                        tester->next = tester->next->next;
                    }
                    delete deleted;
                    size--;
                    return deletedPt;

                }
            }

        }
        validCent = false;
    }

    bool operator==(const Cluster &lhs, const Cluster &rhs){
        NodePtr testerLhs = lhs.points;
        NodePtr testerRhs = rhs.points;
        if (lhs.size == rhs.size) {
            for (int i = 0; i < lhs.size; i++) {
                if (testerLhs->point != testerRhs->point) {
                    testerRhs = testerRhs->next;
                    testerLhs = testerLhs->next;
                    return false;
                }

            }
            return true;
        }
        return false;
    }



    Cluster& Cluster::operator+=(const Point &rhs){
        PointPtr dynPoint = new Point(rhs);
        add(dynPoint);
    }

    Cluster& Cluster::operator-=(const Point &rhs){
        NodePtr tester;
        NodePtr deleted;
        if (*(points->point) == rhs) {

            deleted = points;
            points = points->next;
            delete deleted;
            size--;
            validCent = false;
            return *this;
        }

        else {
            for (NodePtr tester = points; tester != nullptr; tester = tester->next) {

                if (*(tester->next->point) == rhs) {
                    deleted = tester->next;
                    if (tester->next->next == nullptr) {
                        tester->next = nullptr;
                    }
                    else {
                        tester->next = tester->next->next;
                    }
                    delete deleted;
                    size--;
                    validCent = false;
                    return *this;

                }
            }

        }
    }


    bool Cluster::isPresent(NodePtr& head, PointPtr& point){
        NodePtr tester = head;
        while (tester != nullptr){
            if (tester->point == point)
                return true;
            tester = tester->next;

        }
        return false;
    }

    Cluster& Cluster::operator+=(const Cluster &rhs){


        NodePtr testerRhs = rhs.points;

        while (testerRhs != nullptr) {
            if (!isPresent(points, testerRhs->point)) {

                add(testerRhs->point);
            }
            testerRhs = testerRhs->next;
        }

    }

    Cluster& Cluster::operator-=(const Cluster &rhs){


        NodePtr testerRhs = rhs.points;

        while (testerRhs != nullptr) {
            if (isPresent(points, testerRhs->point)) {

                remove(testerRhs->point);
            }
            testerRhs = testerRhs->next;
        }

    }

    const Cluster operator+(const Cluster &lhs, const PointPtr &rhs){
        Cluster tempCluster = lhs;
        tempCluster.add(rhs);
        return tempCluster;

    }

    const Cluster operator-(const Cluster &lhs, const PointPtr &rhs){
        Cluster tempCluster = lhs;
        tempCluster.remove(rhs);
        return tempCluster;

    }

    const Cluster operator+(const Cluster &lhs, const Cluster &rhs){
        Cluster tempCluster = lhs;
        tempCluster += rhs;
        return tempCluster;
    }

    const Cluster operator-(const Cluster &lhs, const Cluster &rhs){
        Cluster tempCluster = lhs;
        tempCluster -= rhs;
        return tempCluster;
    }





    std::ostream &operator<<(std::ostream &os, const Cluster &output) {


        NodePtr tester;
        tester = output.points;

        for (int i = 0; i < output.size; i++) {
            os << *(tester->point);
            tester = tester->next;
            os << output.thisID << std::endl;

        }
        std::cout << std::endl;

        return os;
    }


    std::ifstream &operator>>(std::ifstream &os, Cluster &input) {

        std::string line;
        if (os.is_open()){
            while(getline(os, line)){
                std::stringstream lineStream(line);
                int dimensions = (int) std::count(line.begin(), line.end(), ',');
                PointPtr newPoint = new Point(dimensions + 1);
                lineStream >> *newPoint;
                input.add(newPoint);
            }
            input.pointDimension = input.points->point->getDim();
        }

//        NodePtr tester;
//        tester = input.points;
//        std::cout << "Input Points: " << std::endl;
//        for (int i = 0; i < input.size; i++) {
//            os >> *(tester->point);
//            tester = tester->next;
//
//        }
//        std::cout << std::endl;

        return os;

    }

    void Cluster::SetCent(const Point &copyPoint){// TODO test
        *centroid = copyPoint;
    }

    const Point Cluster::getCent(){// TODO test
        return *centroid;
    }

    void Cluster::computeCent() {// TODO test
        NodePtr tester = points;
        Point temp(pointDimension);
        while (tester != nullptr){
            temp += *tester->point / static_cast<double>(pointDimension);
            tester = tester->next;
        }
        delete centroid;
        centroid = new Point(temp);
        validCent = true;
    }

    bool Cluster::centIsValid(){// TODO test
        return validCent;
    }

    void Cluster::pickPoints(int k, PointPtr *pointArray){ //TODO test
        int step = size / k;
        NodePtr tester = points;
        int j = 0;
        while (tester != nullptr) {
            for (int i = 0; i < step; i++) {
                tester = tester->next;
            }
            pointArray[j] = tester->point;
            j++;
        }
    }





}



