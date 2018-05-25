#ifndef K_MEANS_H
#define K_MEANS_H

#include "clusterclass.h"

using namespace std;

class ClusterClass;

class K_Means
{
public:
    int ClusterAffiliation(vector<double> Element, vector<ClusterClass> Cls);
    vector<ClusterClass> General_K_means(ClusterClass Cl, int sizeK);
    K_Means();
};

#endif // K_MEANS_H
