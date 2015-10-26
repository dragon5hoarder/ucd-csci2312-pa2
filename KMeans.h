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
        Cluster *clusterArray;
    public:

        KMeans(int initK, std::ifstream &os, int Dim);
        KMeans(const KMeans &copyKMeans);
        void operator=(const KMeans &copyKMeans);
        ~KMeans();

        static const double SCORE_DIFF_THRESHOLD;
        double computeClusteringScore();

    };


}

#endif //PA3_INT_KMEANS_H
