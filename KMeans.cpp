//
// Created by dragon5hoarder on 10/25/2015.
//



#include <cmath>
#include <limits>

//#include "KMeans.h"

namespace Clustering{
    template <int k, int dim>
    const double KMeans<k, dim>::SCORE_DIFF_THRESHOLD = 1;

    template <int k, int dim>
    KMeans<k, dim>::KMeans(std::ifstream &os){
        std::ofstream output("output.txt");
        //k = initK;
        //spaceDim = Dim;
        clusterArray = std::vector<Cluster<Point<double, dim>, dim>>(k);
        os >> clusterArray[0];
        for (int i = 1; i < k; i++){
            //clusterArray[i].setDim(spaceDim);
            clusterArray[i].setMap(clusterArray[0].getMap());
        }
        std::vector<Point<double, dim>> initCentroids;
        // sets the centroids for k clusters
        clusterArray[0].pickPoints(k, initCentroids);
        for (int i = 0; i < k; i++){
            clusterArray[i].setCent(initCentroids[i]);
        }
        double score, scoreDiff;
        scoreDiff = SCORE_DIFF_THRESHOLD + 1;
        while (scoreDiff > SCORE_DIFF_THRESHOLD){
            // loop through clusters
            for(int i = 0; i < k; i++){
                // loop through points
                for(int j = 0; j < clusterArray[i].getSize(); j++){
                    Cluster<Point<double, dim>, dim>* minDistClust = &clusterArray[0];
                    double distance = std::numeric_limits<double>::max();
                    // loop through centroids
                    for(int w = 0; w < k; w++){
                        //checks to see which centroid is the closest
                        try{
                            if (clusterArray[i][j].distanceTo(clusterArray[w].getCent()) < distance){
                                minDistClust = &clusterArray[w];
                                distance = clusterArray[i][j].distanceTo(clusterArray[w].getCent());
                            }
                        } catch(OutOfBoundsEx &ex) {
                            std::cerr << ex << std::endl;
                        }

                    }
                    //moves point to cluster with closest centroid
                    if (!(*minDistClust == clusterArray[i])){
                        try {
                            typename Cluster<Point<double, dim>, dim>::Move move(clusterArray[i][j], &clusterArray[i], minDistClust);
                            move.perform();
                            j--;
                        }catch(OutOfBoundsEx &ex) {
                            std::cerr << ex << std::endl;
                        }catch(RemoveFromEmptyEx &ex) {
                            std::cerr << ex << std::endl;
                        }
                    }
                }
            }
            // recalculates each centroid
            for(int i = 0; i < k; i++){
                try{
                    if (!clusterArray[i].centIsValid()){
                        clusterArray[i].computeCent();
                    }
                }catch(RemoveFromEmptyEx &ex) {
                    std::cerr << ex << std::endl;
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

    template <int k, int dim>
    KMeans<k, dim>::~KMeans(){
        //delete [] clusterArray;
    }

    // calculates Beta-CV equation
    template <int k, int dim>
    double KMeans<k, dim>::computeClusteringScore(){
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
