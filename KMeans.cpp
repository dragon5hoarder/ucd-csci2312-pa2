//
// Created by dragon5hoarder on 10/25/2015.
//

#include "KMeans.h"
#include <cmath>
#include <limits>

namespace Clustering{
    const double KMeans::SCORE_DIFF_THRESHOLD = 1;

    KMeans::KMeans(int initK, std::ifstream &os, int Dim){
        std::ofstream output("output.txt");
        k = initK;
        spaceDim = Dim;
        clusterArray = new Cluster[k];
        os >> clusterArray[0];
        PointPtr initCentroids[k];
        // sets the centroids for k clusters
        clusterArray[0].pickPoints(k, initCentroids);
        for (int i = 0; i < k; i++){
            clusterArray[i].setCent(*initCentroids[i]);
        }
        double score, scoreDiff;
        scoreDiff = SCORE_DIFF_THRESHOLD + 1;
        while (scoreDiff > SCORE_DIFF_THRESHOLD){
            // loop through clusters
            for(int i = 0; i < k; i++){
                // loop through points
                for(int j = 0; j < clusterArray[i].getSize(); j++){
                    Cluster* minDistClust = &clusterArray[0];
                    double distance = std::numeric_limits<double>::max();
                    // loop through centroids
                    for(int w = 0; w < k; w++){
                        //checks to see which centroid is the closest
                        if (clusterArray[i][j].distanceTo(clusterArray[w].getCent()) < distance){
                            minDistClust = &clusterArray[w];
                            distance = clusterArray[i][j].distanceTo(clusterArray[w].getCent());
                        }

                    }
                    //moves point to cluster with closest centroid
                    if (!(*minDistClust == clusterArray[i])){
                        Cluster::Move move(&clusterArray[i][j], &clusterArray[i], minDistClust);
                        move.perform();
                        j--;
                    }
                }
            }
            // recalculates each centroid
            for(int i = 0; i < k; i++){
                if (!clusterArray[i].centIsValid()){
                    clusterArray[i].computeCent();
                }
            }
            // uses Beta-CV equation to determine if the points need to be recalculated
            scoreDiff = fabs(score - computeClusteringScore());
        }
        for (int i = 0; i < k; i++){
            output << clusterArray[i] << std::endl;
        }
        std::cout << "printed!" << std::endl;
    }

    KMeans::~KMeans(){
        delete [] clusterArray;
    }

    // calculates Beta-CV equation
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
