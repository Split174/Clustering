#ifndef MIMSPANNINGTREE_H
#define MIMSPANNINGTREE_H

#include "clusterclass.h"

using namespace std;

class ClusterClass;

class MinSpanningTree
{
public:
    MinSpanningTree();
    vector<int> GetMinimalTree(vector<vector<double>> Distance);
    double getR(vector<vector<double>> Distance);
    void DeleteBigEdgeInTree(vector<vector<double> >& Distance, vector<int> Neighbor, double R);
    vector<int> AmountComponentsAndAffiliationElements(vector<vector<double> > Distance, int& AmountCluster);
    vector<ClusterClass> AppendElementsClusters(vector<int> ClusterAffiliation, ClusterClass Source, int AmountCluster);
    vector<ClusterClass> MST_Method(ClusterClass dataElement);
};

#endif // MIMSPANNINGTREE_H
