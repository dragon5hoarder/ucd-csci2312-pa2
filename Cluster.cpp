//
// Created by dragon5hoarder on 9/19/2015.
//

#include "Cluster.h"
#include <cassert>

namespace Clustering {

    Cluster::Cluster() {
        size = 0;
        points = nullptr;
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
    }

    void Cluster::operator=(const Cluster &copyCluster){
        if (this == &copyCluster) {
            return;
        }
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
    }

    Cluster::~Cluster(){
        NodePtr tester = points;
        tester = tester->next;
        NodePtr deleted = points;
        while(tester != nullptr){
            delete deleted;
            deleted = tester;
            tester = tester->next;
        }
        delete deleted;
        points = nullptr;

    }

    // TODO Does not put Points in lexographic order
    const PointPtr& Cluster::add(const PointPtr &addedPt) {
        NodePtr tester;
        NodePtr placeHolder = new Node;
        placeHolder->point = addedPt;
        bool statement = true;
        if (points == nullptr || *(points->point) <= *(placeHolder->point))
        {
            placeHolder->next = points;
            points = placeHolder;
            size++;
            return addedPt;
        }

        else
        {

            tester = points;
            while (tester->next!= nullptr && *(tester->next->point) < *(placeHolder->point))
            {
                tester = tester->next;
            }
            placeHolder->next = tester->next;
            tester->next = placeHolder;
            size++;
            return addedPt;
        }



    }

    const PointPtr& Cluster::remove(const PointPtr &deletedPt) {
        NodePtr tester;
        NodePtr deleted;
        bool statement = true;
        //assert (size == 0);

        if (*(points->point) == *deletedPt) {
            deleted = points;
            points = points->next;
            delete deleted;
            size--;
            return deletedPt;
        }

        for (NodePtr tester = points; tester != nullptr; tester = tester->next) {
            if (*(tester->next->point) == *deletedPt) {
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
            tester = tester->next;
        }
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



    Cluster& Cluster::operator+=(Point &rhs){
        add(&rhs);// TODO Will not compile with the const in parameter
    }

    Cluster& Cluster::operator-=(Point &rhs){
        remove(&rhs);// TODO Will not compile with the const in parameter
    }

    bool Cluster::isPresent(PointPtr& point, NodePtr& head){
        NodePtr tester = head;
        while (tester != nullptr){
            if (tester->point == point)
                return true;
            tester = tester->next;
        }
        return false;
    }

    Cluster& Cluster::operator+=(const Cluster &rhs){
        NodePtr testerLhs = points;
        NodePtr testerRhs = rhs.points;

        while (testerRhs != nullptr) {
            if (!isPresent(testerRhs->point, testerLhs)) {
                add(testerRhs->point);
            }
            testerRhs = testerRhs->next;
        }
        /*do{
            do {

                if (testerLhs->point == testerRhs->point) { //TODO segmentation fault
                    add(testerRhs->point);
                    testerRhs = testerRhs->next;
                    i++;
                    testerLhs = testerLhs->next;
                    j++;
                }
                else {
                    testerRhs = testerRhs->next;
                    i++;
                }
            }while (i < rhs.size);
            testerLhs = testerLhs->next;
            testerRhs = rhs.points;
            i = 0;
            j++;
        }while(j < size);*/
    }

    Cluster& Cluster::operator-=(const Cluster &rhs){
        NodePtr testerLhs = points;
        NodePtr testerRhs = rhs.points;

        while (testerLhs != nullptr) {
            if (!isPresent(testerRhs->point, points)) {
                remove(testerRhs->point);
            }
            testerRhs = testerRhs->next;
        }
        /*do{
            do {

                if (testerLhs->point == testerRhs->point) {
                    remove(testerRhs->point);
                    testerRhs = testerRhs->next;
                    i++;
                    testerLhs = testerLhs->next;
                    j++;
                }
                else {
                    testerRhs = testerRhs->next;
                    i++;
                }
            }while (j < rhs.size);
            testerLhs = testerLhs->next;
            testerRhs = rhs.points;
            i = 0;
            j++;
        }while(i < size);*/
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
    }

    const Cluster operator-(const Cluster &lhs, const Cluster &rhs){
        Cluster tempCluster = lhs;
        tempCluster -= rhs;
    }





    std::ostream &operator<<(std::ostream &os, const Cluster &output) {


        NodePtr tester;
        tester = output.points;
        os << "Points: " << std::endl;
        for (int i = 0; i < output.size; i++) {
            os << *(tester->point);
            tester = tester->next;

        }
        std::cout << std::endl;

        return os;
    }


    std::istream &operator>>(std::istream &os, const Cluster &input) {
        NodePtr tester;
        tester = input.points;
        std::cout << "Input Points: " << std::endl;
        for (int i = 0; i < input.size; i++) {
            os >> *(tester->point);
            tester = tester->next;

        }
        std::cout << std::endl;

        return os;

    }




}



