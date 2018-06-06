#ifndef CLUSTERCLASS_H
#define CLUSTERCLASS_H

#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <cstdlib>
#include <queue>
//#include "clusteringaccuracy.h"


using namespace std;

struct Cluster
{
    vector<vector<double>> Distance;
    vector<double> Centroid;
    vector<vector<double>> Elements;
    Cluster(int NumberOfObject=0, int NumberOfVariables=0)
    {
        //NumOfObject = _NumberOfObject;
        Elements = vector<vector<double>>(NumberOfObject, vector <double>(NumberOfVariables));
    }
};

#endif // CLUSTERCLASS_H
