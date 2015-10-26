//
// Created by dragon5hoarder on 10/25/2015.
//

#ifndef PA3_INT_KMEANS_H
#define PA3_INT_KMEANS_H

#include <fstream>
#include "Cluster.h"

namespace Clustering {

    class KMeans{

    private:
        int k;
        int spaceDim;
        //holds k clusters
        Cluster *clusterArray;
    public:
        // Constructors
        KMeans(int initK, std::ifstream &os, int Dim); //only constructor needed, runs the entire program
        //TODO exception- no copy or assignment op
        ~KMeans();

        // an arbitrary number made up by me to end the clustering calculation
        static const double SCORE_DIFF_THRESHOLD;
        // calculates the score
        double computeClusteringScore();

    };


}

#endif //PA3_INT_KMEANS_H
