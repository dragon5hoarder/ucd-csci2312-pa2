//
// Created by dragon5hoarder on 9/19/2015.
//


#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cstdlib>

//#include "Cluster.h"


namespace Clustering {
    template <typename T, int dim>
    int Cluster<T, dim>::clustID = 0;

    template <typename T, int dim>
    Cluster<T, dim>::Cluster() {
        size = 0;

        thisID = clustID++;
        //pointDimension = 0;
        centroid();
        validCent = false;
    }

    template <typename T, int dim>
    Cluster<T, dim>::Cluster(const Cluster<T, dim> &copyCluster) {
        size = copyCluster.size;
        auto copyIt = copyCluster.points.begin();
        auto it = points.before_begin();
        for (int i = 0; i < size; i++){
            points.insert_after(it++, *copyIt);
            copyIt++;
        }

        thisID = clustID++;
        //pointDimension = copyCluster.pointDimension;
        centroid();
        validCent = copyCluster.validCent;
    }

    template <typename T, int dim>
    void Cluster<T, dim>::operator=(const Cluster<T, dim> &copyCluster){
        if (this == &copyCluster) {
            return;
        }
        size = copyCluster.size;
        clear();

        auto copyIt = copyCluster.points.begin();
        auto it = points.before_begin();
        for (int i = 0; i < size; i++){
            points.insert_after(it++, *copyIt);
            copyIt++;
        }

        //pointDimension = copyCluster.pointDimension;
        //centroid = new T();
        centroid = *copyCluster.centroid;
        validCent = copyCluster.validCent;

    }

    template <typename T, int dim>
    Cluster<T, dim>::~Cluster(){
        //clear();
        //delete centroid;

    }

    template <typename T, int dim>
    void Cluster<T, dim>::clear(){
        points.clear();
    }



    template <typename T, int dim>
    void Cluster<T, dim>::add(const T &addedPt) {



        bool statement = true;
        try {
            auto it = points.begin();
            if (points.empty() || *it >= addedPt) {

                points.push_front(addedPt);
                size++;
            }
            else
            {


                auto previousIt = points.begin();
                while (it != points.end() && *it < addedPt)
                {
                    previousIt = it;
                    it++;
                }

                points.insert_after(previousIt, addedPt);
                size++;
            }
        } catch(DimensionalityMismatchEx &ex) {
            std::cerr << ex << std::endl;
        }


        validCent = false;
    }

    template <typename T, int dim>
    const T& Cluster<T, dim>::remove(const T &deletedPt) {
        if (size == 0)
            throw RemoveFromEmptyEx(0);

        try {
            points.remove(deletedPt);
            size--;


        }catch(DimensionalityMismatchEx &ex) {
            std::cerr << ex << std::endl;
        }
        validCent = false;
        return deletedPt;
    }

    template <typename S, int dim3>
    bool operator==(const Cluster<S, dim3> &lhs, const Cluster<S, dim3> &rhs){
        if (lhs.thisID == rhs.thisID)
            return true;
        return false;
//        auto lhsIt = lhs.points.begin();
//        auto rhsIt = rhs.points.begin();
//        if (lhs.size == rhs.size) {
//            for (int i = 0; i < lhs.size; i++) {
//                try {
//                    if (*lhsIt != *rhsIt) {
//                        return false;
//                    }
//                }catch(DimensionalityMismatchEx &ex) {
//                    std::cerr << ex << std::endl;
//                }
//                lhsIt++;
//                rhsIt++;
//
//            }
//            return true;
//        }
//        return false;
    }



    template <typename T, int dim>
    Cluster<T, dim>& Cluster<T, dim>::operator+=(const T &rhs){
        //Point dynPoint(rhs);
        add(rhs);
    }

    template <typename T, int dim>
    Cluster<T, dim>& Cluster<T, dim>::operator-=(const T &rhs){
        remove(rhs);
//        NodePtr tester;
//        NodePtr deleted;
//        try {
//            if (*points->point == rhs) {
//
//                deleted = points;
//                points = points->next;
//                delete deleted;
//                size--;
//                validCent = false;
//                return *this;
//            }
//
//
//            else {
//                for (NodePtr tester = points; tester != nullptr; tester = tester->next) {
//
//                    if (*tester->next->point == rhs) {
//                        deleted = tester->next;
//                        if (tester->next->next == nullptr) {
//                            tester->next = nullptr;
//                        }
//                        else {
//                            tester->next = tester->next->next;
//                        }
//                        delete deleted;
//                        size--;
//                        validCent = false;
//                        return *this;
//
//                    }
//                }
//
//            }
//        }catch(DimensionalityMismatchEx &ex) {
//            std::cerr << ex << std::endl;
//        }
    }


    template <typename T, int dim>
    bool Cluster<T, dim>::isPresent(const T& point){
        auto it = points.begin();
        while (it != points.end()){
            if (*it == point)
                return true;
            it++;

        }
        return false;
    }

    template <typename T, int dim>
    Cluster<T, dim>& Cluster<T, dim>::operator+=(const Cluster<T, dim> &rhs){


        auto rhsIt = rhs.points.begin();

        while (rhsIt != points.end()) {
            if (!isPresent(*rhsIt)) {

                add(*rhsIt);
            }
            rhsIt++;
        }

    }

    template <typename T, int dim>
    Cluster<T, dim>& Cluster<T, dim>::operator-=(const Cluster<T, dim> &rhs){


        auto rhsIt = rhs.points.begin();

        while (rhsIt != points.end()) {
            if (isPresent(*rhsIt)) {
                remove(*rhsIt);
            }
            rhsIt++;
        }

    }

    template <typename S, int dim3>
    const Cluster<S, dim3> operator+(const Cluster<S, dim3> &lhs, const S &rhs){
        Cluster<S, dim3> tempCluster = lhs;
        tempCluster.add(rhs);
        return tempCluster;

    }

    template <typename S, int dim3>
    const Cluster<S, dim3> operator-(const Cluster<S, dim3> &lhs, const S &rhs){
        Cluster<S, dim3> tempCluster = lhs;
        tempCluster.remove(rhs);
        return tempCluster;

    }

    template <typename S, int dim3>
    const Cluster<S, dim3> operator+(const Cluster<S, dim3> &lhs, const Cluster<S, dim3> &rhs){
        Cluster<S, dim3> tempCluster = lhs;
        tempCluster += rhs;
        return tempCluster;
    }

    template <typename S, int dim3>
    const Cluster<S, dim3> operator-(const Cluster<S, dim3> &lhs, const Cluster<S, dim3> &rhs){
        Cluster<S, dim3> tempCluster = lhs;
        tempCluster -= rhs;
        return tempCluster;
    }





    template <typename S, int dim3>
    std::ostream &operator<<(std::ostream &os, const Cluster<S, dim3> &output) {



        auto it = output.points.begin();

        for (int i = 0; i < output.size; i++) {
            os << *it;
            it++;
            os << output.thisID << std::endl;

        }
        os <<  output.centroid << " centroid" << std::endl;

        return os;
    }


    template <typename S, int dim3>
    std::ifstream &operator>>(std::ifstream &os, Cluster<S, dim3> &input) {

        std::string line;
        if (os.is_open()){
            getline(os, line);
            //input.pointDimension = (int) std::count(line.begin(), line.end(), ',') + 1;
            os.seekg(0, os.beg);
            while(getline(os, line)){
                std::stringstream lineStream(line);
                int dimensions = (int) std::count(line.begin(), line.end(), ',');
                try {
                    if ((dimensions + 1) != dim3)
                        throw DimensionalityMismatchEx(3);
                    S newPoint;
                    lineStream >> newPoint;
                    input.add(newPoint);
                    input.imported++;
                }catch(DimensionalityMismatchEx &ex) {
                    std::cerr << ex << std::endl;
                    input.failed++;
                }
            }
        }
        std::cout << "Imported: " << input.numberImported() << " Failed: " << input.numberFailed() << std::endl;

//        NodePtr tester;
//        tester = input.points;
//        std::cout << "Input Points: " << std::endl;
//        for (int i = 0; i < input.size; i++) {
//            os >> *(tester->point);
//            tester = tester->next;
//
//        }
//        std::cout << std::endl;
        input.createMap();
        input.printMap();
        return os;

    }

    template <typename T, int dim>
    void Cluster<T, dim>::setCent(const T &copyPoint){
        try {
            centroid = copyPoint;
        }catch(DimensionalityMismatchEx &ex) {
            std::cerr << ex << std::endl;
        }
    }

    template <typename T, int dim>
    const T Cluster<T, dim>::getCent(){
        return centroid;
    }

    template <typename T, int dim>
    void Cluster<T, dim>::computeCent() {
        auto it = points.begin();
        //pointDimension = it->getDim();
        T temp();

        if (size == 0)
            throw RemoveFromEmptyEx(1);

        while (it != points.end()){
            try {
                temp += *it / static_cast<double>(size);
            }catch(DimensionalityMismatchEx &ex) {
                std::cerr << ex << std::endl;
            }
            it++;
        }
        //delete centroid;
        try {
            centroid = temp;
            validCent = true;
        }catch(DimensionalityMismatchEx &ex) {
            std::cerr << ex << std::endl;
        }

    }

    template <typename T, int dim>
    bool Cluster<T, dim>::centIsValid(){
        return validCent;
    }

    template <typename T, int dim>
    void Cluster<T, dim>::pickPoints(int k, std::vector<T> &pointArray){
        int step = size / k;
        auto it = points.begin();
        pointArray.push_back(*it);

         for (int i = 1; i < k; i++){
             int j = 0;
             while (it != points.end() && j < step){
                it++;
                j++;
            }
            pointArray.push_back(*it);

        }
    }

    template <typename T, int dim>
    T &Cluster<T, dim>::operator[](int index) {
        if (index >= size)
            throw OutOfBoundsEx(1);
        auto it = points.begin();

        int i = 0;
        while (it != points.end()){
            if (i == index) {
                return *it;
            }
            else{
                i ++;
                it++;
            }
        }

    }

    template <typename T, int dim>
    double Cluster<T, dim>::intraClusterDistance(){
        auto it1 = points.begin();
        auto it2 = points.begin();

        double sum = 0;
        for (int i = 0; i < size; i++){
            for (int j = 0; j < size; j++){
                DPKey<T> key(*it1, *it2);
                sum += (distances.find(key))->second;
                it2++;
            }
            it1++;
            it2 = points.begin();
        }
        return sum / 2;
    }

    template <typename S, int dim3>
    double interClusterDistance(Cluster<S, dim3> &c1, Cluster<S, dim3> &c2){
        double sum = 0;
        auto it1 = c1.points.begin();
        auto it2 = c2.points.begin();
        for (int i = 0; i < c1.size; i++){
            for (int j = 0; j < c2.size; j++){
                DPKey<S> key(*it1, *it2);
                sum += (c1.distances.find(key))->second;
                it2++;
            }
            it1++;
            it2 = c2.points.begin();
        }
        return sum;
    }

    template <typename T, int dim>
    int Cluster<T, dim>::getClusterEdges(){
        return size * (size - 1) / 2;
    }

    template <typename S, int dim3>
    double interClusterEdges(const Cluster<S, dim3> &c1, const Cluster<S, dim3> &c2){
        return c1.size * c2.size;
    }

    template <typename T, int dim>
    bool Cluster<T, dim>::contains(const T &pnt){

        if (isPresent(pnt))
            return true;

        return false;
    }

    template <typename T, int dim>
    void Cluster<T, dim>::createMap() {
        for (auto ito = points.begin(); ito != points.end(); ++ ito) {
            auto iti = ito;
            ++ iti; // Start the inner iterator at the next value to avoid repeating points
            for (; iti != points.end(); ++ iti) {
//                std::cout << *ito << ito->getId() << ", " << *iti << iti->getId() << std::endl; // Uncomment to see the points...
//                std::cout << "DISTANCE: " << ito->distanceTo(*iti) << std::endl; // ...and the distance
                DPKey<T> key(*ito, *iti);
                auto search = distances.find(key); // check if it is there already (won't be :))
                if (search == distances.end())
                    distances[key] = ito->distanceTo(*iti);
            }
        }
    }

    template <typename T, int dim>
    void Cluster<T, dim>::printMap() {
        std::cout << std::endl <<  "Print out map" << std::endl;
        for (auto it = distances.begin(); it != distances.end(); ++ it)
            std::cout
            << "{{"
            << it->first.p1.getId() // Note that the entries of the map are of type std::pair
            << ", "
            << it->first.p2.getId()
            << "}, "
            << it->second
            << "}"
            << std::endl;
    }





}



