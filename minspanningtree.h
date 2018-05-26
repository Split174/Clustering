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
    vector<int> AmountComponentsAndAffiliationElements(ClusterClass C, int& AmountCluster);
    vector<ClusterClass> AppendElementsClusters(vector<int> ClusterAffiliation, ClusterClass Source, int AmountCluster);
    vector<ClusterClass> MST_Method(ClusterClass Cl);
};

#endif // MIMSPANNINGTREE_H
