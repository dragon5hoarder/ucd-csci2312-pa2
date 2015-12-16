//
// Created by dragon5hoarder on 10/25/2015.
//

#ifndef PA3_INT_KMEANS_H
#define PA3_INT_KMEANS_H

#include <fstream>
#include <cmath>
#include <limits>

#include "Cluster.h"

namespace Clustering {

    template <int k, int dim>
    class KMeans{

    private:
        //int k;
        //int spaceDim;
        //holds k clusters
        std::vector<Cluster<Point<double, dim>, dim>> clusterArray;
    public:
        // Constructors
        // only constructor needed, runs the entire program
        // user dictates what the input file is
        KMeans(std::ifstream &os);
        KMeans(KMeans &copyK) = delete;

        ~KMeans();

        // an arbitrary number made up by me to end the clustering calculation
        static const double SCORE_DIFF_THRESHOLD;
        // calculates the score
        double computeClusteringScore();

    };


}

#include "KMeans.cpp"
#endif //PA3_INT_KMEANS_H
