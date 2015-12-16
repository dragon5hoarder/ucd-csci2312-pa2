//
// Created by dragon5hoarder on 9/19/2015.
//

#ifndef INT_PA2_CLUSTER_H
#define INT_PA2_CLUSTER_H

#include <forward_list>
#include <unordered_map>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cstdlib>

#include "Point.h"

namespace Clustering {

    template <typename T>
    struct DPKey { // key {p1, p2}
        T p1, p2;
        DPKey(const T &dp1, const T &dp2) :
                p1(dp1), p2(dp2)
        {}
    };

    template <typename T>
    struct DPKeyHash { // hash functor
        std::size_t operator()(const DPKey<T> &key) const { // note the const
            unsigned int
                    u1 = key.p1.getId(),
                    u2 = key.p2.getId();

            if (u1 > u2) std::swap(u1, u2); // ascending order

            return std::hash<std::size_t>()((u1 + u2) * (u1 + u2 + 1) / 2 + u2);
        }
    };

    template <typename T>
    struct DPKeyEqual { // equality functor (implements transitivity)
        bool operator()(const DPKey<T> &lhs, const DPKey<T> &rhs) const { // note the const
            return (lhs.p1.getId() == rhs.p1.getId() && lhs.p2.getId() == rhs.p2.getId()) ||
                   (lhs.p1.getId() == rhs.p2.getId() && lhs.p2.getId() == rhs.p1.getId());
        }
    };


//    template <typename T, int dim>
//    typedef T *PointPtr;
//    typedef struct Node *NodePtr;

//    struct Node{
//        PointPtr point;
//        Node *next;
//    };

    template <typename T, int dim>
    class Cluster{

    private:
        std::forward_list<T> points;
        int size;
        static int clustID;
        int thisID;
        //int pointDimension;
        T centroid;
        bool validCent;

        unsigned int failed;
        unsigned int imported;

        bool isPresent(const T& point);

        std::unordered_map<DPKey<T>, double, DPKeyHash<T>, DPKeyEqual<T>> distances;

        void createMap();
        void printMap();


    public:
        Cluster();
        Cluster(const Cluster &copyCluster);
        void operator=(const Cluster &copyCluster);
        ~Cluster();

        // Set functions
        void clear();

        void add(const T &addedPt);

        const T& remove(const T &deletedPt);

        // Centroid Operators
        void setCent(const T &copyPoint);
        const T getCent();
        void computeCent();
        bool centIsValid();

        void pickPoints(int k, std::vector<T> &pointArray);
        int getSize() { return size; }
        //void setDim(int dim) { pointDimension = dim; }

        bool contains(const T &pnt);

        std::unordered_map<DPKey<T>, double, DPKeyHash<T>, DPKeyEqual<T>> &getMap() { return distances; }
        void setMap(std::unordered_map<Clustering::DPKey<T>, double, Clustering::DPKeyHash<T>, Clustering::DPKeyEqual<T>> &copyMap) { distances = copyMap; }


        // overloaded operators
        template <typename W, int dim2>
        friend bool operator==(const Cluster<W, dim2> &lhs, const Cluster<W, dim2> &rhs);

        Cluster &operator+=(const T &rhs); // add point
        Cluster &operator-=(const T &rhs); // remove point

        Cluster &operator+=(const Cluster &rhs); // union
        Cluster &operator-=(const Cluster &rhs); // difference

        template <typename W, int dim2>
        friend const Cluster<W, dim2> operator+(const Cluster<W, dim2> &lhs, const T &rhs);
        template <typename W, int dim2>
        friend const Cluster<W, dim2> operator-(const Cluster<W, dim2> &lhs, const T &rhs);

        template <typename W, int dim2>
        friend const Cluster<W, dim2> operator+(const Cluster<W, dim2> &lhs, const Cluster<W, dim2> &rhs);
        template <typename W, int dim2>
        friend const Cluster<W, dim2> operator-(const Cluster<W, dim2> &lhs, const Cluster<W, dim2> &rhs);

        T &operator[](int index);

        //calcutaes the distances between points to calculate the Beta-CV equation
        double intraClusterDistance();
        template <typename W, int dim2>
        friend double interClusterDistance(Cluster<W, dim2> &c1, Cluster<W, dim2> &c2);
        int getClusterEdges();
        template <typename W, int dim2>
        friend double interClusterEdges(const Cluster<W, dim2> &c1, const Cluster<W, dim2> &c2);

        // class wich moves a point to anther cluster and removes it from original
        class Move {
        private:
            T ptr;
            Cluster *from, *to;
        public:
            Move(const T ptr, Cluster *from, Cluster *to) : ptr(ptr), from(from), to(to) {}
            void perform() {to->add(from->remove(ptr));}
        };



        // IO
        template <typename W, int dim2>
        friend std::ostream &operator<<(std::ostream &os, const Cluster<W, dim2> &output);
        template <typename W, int dim2>
        friend std::ifstream &operator>>(std::ifstream &os, Cluster<W, dim2> &input);

        unsigned int numberImported() { return imported; }
        unsigned int numberFailed() {return failed; }


    };








}

#include "Cluster.cpp"

#endif //INT_PA2_CLUSTER_H
