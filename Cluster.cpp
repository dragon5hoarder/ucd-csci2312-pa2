//
// Created by dragon5hoarder on 9/19/2015.
//

#include "Cluster.h"

using namespace Clustering;

Cluster::Cluster(){
    size = 0;
    points = nullptr;
}

Cluster::Cluster(const Cluster& copyCluster){
    size = copyCluster.size;

}

void Cluster::add(const PointPtr& addedPt){

}

//const PointPtr Cluster::&remove(const PointPtr &){

//}
