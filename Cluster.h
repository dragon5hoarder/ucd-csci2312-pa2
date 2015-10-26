//
// Created by dragon5hoarder on 9/19/2015.
//

#ifndef INT_PA2_CLUSTER_H
#define INT_PA2_CLUSTER_H

#include "Point.h"

namespace Clustering {
    typedef Point *PointPtr;
    typedef struct Node *NodePtr;

    struct Node{
        PointPtr point;
        Node *next;
    };

    class Cluster{

    private:
        NodePtr points;
        int size;
        static int clustID;
        int thisID;
        int pointDimension;
        PointPtr centroid;
        bool validCent;

        bool isPresent(NodePtr& head, PointPtr& point);

        bool isPresent(PointPtr& point, NodePtr& head);


    public:
        Cluster();
        Cluster(const Cluster &copyCluster);
        void operator=(const Cluster &copyCluster);
        ~Cluster();

        // Set functions
        void clear();

        void add(const PointPtr &addedPt);

        const PointPtr& remove(const PointPtr &deletedPt);

        // Centroid Operators
        void setCent(const Point &copyPoint);
        const Point getCent();
        void computeCent();
        bool centIsValid();

        void pickPoints(int k, PointPtr *pointArray);
        int getSize() { return size; }


        // overloaded operators
        friend bool operator==(const Cluster &lhs, const Cluster &rhs);

        Cluster &operator+=(const Point &rhs); // add point
        Cluster &operator-=(const Point &rhs); // remove point

        Cluster &operator+=(const Cluster &rhs); // union
        Cluster &operator-=(const Cluster &rhs); // difference

        friend const Cluster operator+(const Cluster &lhs, const PointPtr &rhs);
        friend const Cluster operator-(const Cluster &lhs, const PointPtr &rhs);

        friend const Cluster operator+(const Cluster &lhs, const Cluster &rhs);
        friend const Cluster operator-(const Cluster &lhs, const Cluster &rhs);

        Point &operator[](int index) const;

        double intraClusterDistance() const;
        friend double interClusterDistance(const Cluster &c1, const Cluster &c2);
        int getClusterEdges();
        friend double interClusterEdges(const Cluster &c1, const Cluster &c2);

        class Move {
        private:
            PointPtr ptr;
            Cluster *from, *to;
        public:
            Move(const PointPtr ptr, Cluster *from, Cluster *to) : ptr(ptr), from(from), to(to) {}
            void perform() {to->add(from->remove(ptr));}
        };




        friend std::ostream &operator<<(std::ostream &os, const Cluster &output);
        friend std::ifstream &operator>>(std::ifstream &os, Cluster &input);
    };

}

#endif //INT_PA2_CLUSTER_H
