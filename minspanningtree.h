#ifndef MIMSPANNINGTREE_H
#define MIMSPANNINGTREE_H

#include "clusterclass.h"

using namespace std;

class ClusterClass;

class MinSpanningTree
{
public:
    MinSpanningTree();
    vector<int> GetMinimalTree(ClusterClass C);
    double getR(ClusterClass C);
    void DeleteBigEdge(ClusterClass &C, vector<int> Neighbor, double R);
    void ClusterMinimalTree(ClusterClass C);
    void General_MST(ClusterClass Cl);
};

#endif // MIMSPANNINGTREE_H
