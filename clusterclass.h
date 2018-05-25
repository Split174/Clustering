#ifndef CLUSTERCLASS_H
#define CLUSTERCLASS_H

#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <cstdlib>
#include <queue>
#include "k_means.h"

//#include "myrand.h"


using namespace std;
// TODO надо что бы элементы кластера были составные, а не просто вектор double

class K_Means;
class MinSpanningTree;

class ClusterClass
{
private:
    //int num; // номер кластера ( читай имя)
    vector<vector<double>> Distance; // расстояние элемента i до элемента j
    vector<double> Centroid;
    vector<vector<double>> Elements; // элементы содержащиеся в кластере
public:
    friend class K_Means;
    friend class MinSpanningTree;

    void CalcDistance();
    friend void MoveElement(ClusterClass &C1, ClusterClass &C2, int indexElement);

    ClusterClass(); //
    ClusterClass(int NumberOfObject, int NumberOfVariables); // ну тут из названия

    void RecalculateCentroids();

    vector<double>&  operator[](int row);
    friend ostream& operator <<(ostream &os, ClusterClass &C);
    friend double DistanceFormObjToObj(vector<double> Obj1, vector<double> Obj2);
    friend int main();
};

#endif // CLUSTERCLASS_H
