#ifndef CLUSTERCLASS_H
#define CLUSTERCLASS_H

#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <cstdlib>
#include <queue>

//#include "myrand.h"

using namespace std;
// TODO надо что бы элементы кластера были составные, а не просто вектор double
class ClusterClass
{
private:
    //int num; // номер кластера ( читай имя)
    vector<vector<double>> Distance; // расстояние элемента i до элемента j
    vector<double> Centroid;
    vector<vector<double>> Elements; // элементы содержащиеся в кластере
public:
    void CalcDistance();
    friend void MoveElement(ClusterClass &C1, ClusterClass &C2, int indexElement);
    friend vector<ClusterClass> K_Means(ClusterClass Cl, int sizeK);
    friend int ClusterAffiliation(vector<double> Element, vector<ClusterClass> Cls);
    ClusterClass(); //
    ClusterClass(int NumberOfObject, int NumberOfVariables); // ну тут из названия
    void RecalculateCentroids();
    vector<double>&  operator[](int row);
    friend ostream& operator <<(ostream &os, ClusterClass &C);
    friend double DistanceFormObjToObj(vector<double> Obj1, vector<double> Obj2);
    friend int main();
    vector<int> GetMinimalTree();
    double getR();
    void DeleteBigEdge(vector<int> Neighbor, double R);
    void ClusterMinimalTree();
};

#endif // CLUSTERCLASS_H
