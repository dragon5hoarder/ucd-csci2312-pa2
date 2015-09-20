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

    public:
        Cluster();
        Cluster(const Cluster &);
        Cluster &operator=(const Cluster &);
        ~Cluster();

        // Set functions
        void add(const PointPtr &);
        const PointPtr &remove(const PointPtr &);

    };

}

#endif //INT_PA2_CLUSTER_H
