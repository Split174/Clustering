#include "clusterclass.h"
#include <generatepoint.h>
using namespace std;

void MoveElement(ClusterClass &C1, ClusterClass &C2, int indexElement)
{
    C2.Elements.push_back(C1.Elements[indexElement]);
    C1.Elements.erase(C1.Elements.begin() + indexElement - 1);
}

int main()
{
    GeneratePoint(100, 2000);
    int n,m, k=1;
    ifstream mat("in.txt");
    ofstream Kmeansfile("kmeans.txt");
    ofstream MSTfile("mst.txt");
    mat >> n;
    mat >> m;
    ClusterClass GeneralCluster(n,m);
    for(int i=0; i<n; i++)
        for (int j=0; j<m; j++)
            mat >> GeneralCluster[i][j];
    MinSpanningTree MST;
    vector<ClusterClass> MSTClusters = MST.MST_Method(GeneralCluster);
    CreatePng(MSTClusters, "MST.png");
    for (size_t i = 0; i < MSTClusters.size(); i++)
    {
        MSTfile << "Cluster № " << i << endl;
        MSTClusters[i].RecalculateCentroids();
        MSTfile << MSTClusters[i] << endl;
    }
    MSTfile << "Q for MST = " << ClusteringAccuracy(MSTClusters) << endl;
    cout << "MST finish" << endl;


    K_Means KM;
    double Q = 10;
    vector<ClusterClass> KMeansClusters;
    while(true)
    {
        k++;
        cout << k << endl;
        KMeansClusters = KM.General_K_means(GeneralCluster, k);
        double tmp = ClusteringAccuracy(KMeansClusters);
        if (tmp > Q || tmp < 0.3)
            break;
        else
            Q = tmp;;
    }
    CreatePng(KMeansClusters, "Kmeans.png");
    for (size_t i = 0; i < KMeansClusters.size(); i++)
    {
        Kmeansfile << "Cluster № " << i << endl;
        Kmeansfile << KMeansClusters[i] << endl;
    }
    Kmeansfile << "Q for Kmeans = " << ClusteringAccuracy(KMeansClusters) << endl;
    cout << "Kmeans finish" << endl;
    return 0;
}
