//
// Created by dragon5hoarder on 10/25/2015.
//

#include "KMeans.h"
#include <cmath>
#include <gmpxx.h>

namespace Clustering{
    const double KMeans::SCORE_DIFF_THRESHOLD = 1;

    KMeans::KMeans(int initK, std::ifstream &os, int Dim){
        std::ofstream output("output.txt");
        k = initK;
        spaceDim = Dim;
        clusterArray = new Cluster[k];
        os >> clusterArray[0];
        PointPtr initCentroids[k];
        clusterArray[0].pickPoints(k, initCentroids);
        for (int i = 0; i < k; i++){
            clusterArray[i].setCent(*initCentroids[i]);
        }
        double score, scoreDiff;
        scoreDiff = SCORE_DIFF_THRESHOLD + 1;
        while (scoreDiff > SCORE_DIFF_THRESHOLD){
            for(int i = 0; i < k; i++){// loop through clusters
                for(int j = 0; j < clusterArray[i].getSize(); j++){// loop through points
                    Cluster* minDistClust = &clusterArray[0];
                    double distance = std::numeric_limits<double>::max();
                    for(int w = 0; w < k; w++){// loop through centroids
                        if (clusterArray[i][j].distanceTo(clusterArray[w].getCent()) < distance){
                            minDistClust = &clusterArray[w];
                            distance = clusterArray[i][j].distanceTo(clusterArray[w].getCent());
                        }

                    }
                    if (!(*minDistClust == clusterArray[i])){
                        Cluster::Move move(&clusterArray[i][j], &clusterArray[i], minDistClust);
                        move.perform();
                        j--;
                    }
                }
            }
            for(int i = 0; i < k; i++){
                if (!clusterArray[i].centIsValid()){
                    clusterArray[i].computeCent();
                }
            }
            scoreDiff = fabs(score - computeClusteringScore());
        }
        for (int i = 0; i < k; i++){
            output << clusterArray[i] << std::endl;
        }
        std::cout << "printed!" << std::endl;
    }

    KMeans::KMeans(const KMeans &copyKMeans){
        std::cout << "Unable to copy for now" << std::endl;
    }

    void KMeans::operator=(const KMeans &copyKMeans){
        std::cout << "Unable to copy for now" << std::endl;
    }

    KMeans::~KMeans(){
        delete [] clusterArray;
    }

    double KMeans::computeClusteringScore(){
        double result, Din = 0, Dout = 0, Pin = 0, Pout = 0;
        for(int i = 0; i < k; i++){
            Din += clusterArray[i].intraClusterDistance();
            Pin += clusterArray[i].getClusterEdges();
            for (int j = i+1; j < k; j++){
                Dout += interClusterDistance(clusterArray[i], clusterArray[j]);
                Pout += interClusterEdges(clusterArray[i], clusterArray[j]);
            }
        }
        result = ((Din / Pin) / (Dout / Pout));
        return result;
    }
}
