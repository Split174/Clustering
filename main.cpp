#include "cluster.h"
#include <minspanningtree.h>
#include <generatepoint.h>
#include <createclustermap.h>
#include <clusteringaccuracy.h>
#include <generalfunc.h>
#include <kmeans.h>
#include <time.h>
using namespace std;

void kmeans(Cluster GeneralCluster)
{
    ofstream Kmeansfile("kmeans.txt");
    vector<Cluster> KMeansClusters, KMeansClustersTmp1, KMeansClustersTmp2;
    KMeansClustersTmp1 = General_K_means(GeneralCluster, 4);
    KMeansClustersTmp2 = General_K_means(GeneralCluster, 5);
    double Q1 = ClusteringAccuracy(KMeansClustersTmp1);
    double Q2 = ClusteringAccuracy(KMeansClustersTmp2);
    double Q;
    int k;
    if (Q1 < Q2)
    {
        Q = Q1;
        k = 4 ;
        KMeansClusters = KMeansClustersTmp1;
    }
    else
    {
        Q = Q2;
        k = 5;
        KMeansClusters = KMeansClustersTmp2;
    }
    while(Q>0.4)
    {
        if (Q1 < Q2)
            k--;
        else
            k++;
        cout << k << "\n";
        KMeansClusters = General_K_means(GeneralCluster, k);
        Q = ClusteringAccuracy(KMeansClusters);
        cout << " " << Q << "\n";
    }
    CreatePng(KMeansClusters, "Kmeans.png");
    for (size_t i = 0; i < KMeansClusters.size(); i++)
    {
        Kmeansfile << "Cluster № " << i << endl;
        Kmeansfile << KMeansClusters[i] << endl;
    }
    Kmeansfile << "Q for Kmeans = " << Q << "\n";
    cout << "Kmeans finish" << "\n";
}
void mst(Cluster GeneralCluster)
{
    ofstream MSTfile("mst.txt");
    vector<Cluster> MSTClusters = MST_Method(GeneralCluster);
    CreatePng(MSTClusters, "MST.png");
    for (size_t i = 0; i < MSTClusters.size(); i++)
    {
        MSTfile << "Cluster № " << i << "\n";
        RecalculateCentroids(MSTClusters[i]);
        MSTfile << MSTClusters[i] << "\n";
    }
    double Q = ClusteringAccuracy(MSTClusters);
    MSTfile << "Q for MST = " << Q << "\n";
    cout << "MST finish" << "\n";
}

int main()
{
    cout << "Выберете вариант работы программы" << "\n" << "1 - свой набор данных" << "\n" << "2 - сгенерированный набор" << endl;
    int answer;
    cin >> answer;
    string file;
    int AmountPoint, Radius;
    switch (answer)
    {
    case 1:
        file = "my.txt";
        break;
    case 2:
        file = "generate.txt";
        cout << "Введите количество точек и радиус:";
        cin >> AmountPoint;
        cin >> Radius;
        GeneratePoint(Radius, AmountPoint);
        break;
    }
    int n,m;
    ifstream mat(file);
    mat >> n;
    mat >> m;
    Cluster GeneralCluster(n,m);
    for(int i=0; i<n; i++)
        for (int j=0; j<m; j++)
            mat >> GeneralCluster.Elements[i][j];
    clock_t currentTime;
    currentTime = clock();
    mst(GeneralCluster);
    currentTime = clock() - currentTime;
    cout << "Время работы MST: " << (double)currentTime / CLOCKS_PER_SEC << "\n";
    currentTime = clock();
    kmeans(GeneralCluster);
    currentTime = clock() - currentTime;
    cout << "Время работы Kmeans: " << (double)currentTime / CLOCKS_PER_SEC << "\n";
    return 0;
}
