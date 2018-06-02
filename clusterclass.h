#ifndef CLUSTERCLASS_H
#define CLUSTERCLASS_H

#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <cstdlib>
#include <queue>
#include "k_means.h"
#include "minspanningtree.h"
//#include "clusteringaccuracy.h"


using namespace std;
class K_Means;
class MinSpanningTree;

class ClusterClass
{
private:
    vector<vector<double>> Distance;
    vector<double> Centroid;
    vector<vector<double>> Elements;
public:
    friend class K_Means;
    friend class MinSpanningTree;
    friend double ClusteringAccuracy(vector<ClusterClass>);
    friend double AverageDistanceBetweenClusters(vector<ClusterClass> data);
    friend double AverageDistanceInsideAllCluster(vector<ClusterClass> data);

    void CalcDistance();
    friend void MoveElement(ClusterClass &C1, ClusterClass &C2, int indexElement);

    ClusterClass(); //
    ClusterClass(int NumberOfObject, int NumberOfVariables); // ну тут из названия
    double AverageDistanceInsideCluster();
    void RecalculateCentroids();

    vector<double>&  operator[](int row);
    friend ostream& operator <<(ostream &os, ClusterClass &C);
    friend double DistanceFormObjToObj(vector<double> Obj1, vector<double> Obj2);
    friend int main();
    friend void  DrawCluster(ClusterClass Source, vector<char> Color, char*& dataPoint);
    friend void  CreatePng(vector<ClusterClass> dataClusters, string file);
};

#endif // CLUSTERCLASS_H
