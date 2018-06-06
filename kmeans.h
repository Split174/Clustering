#include "cluster.h"

int ClusterAffiliation(vector<double> Element, vector<Cluster> data)
{
    //cout << "ClusterAffiliation" << endl;
    int indexMinCluster=0;
    double min = 99999;
    double tmp=0;
    for (size_t i = 0; i < data.size(); i++)
    {
        for (size_t j = 0; j < data[i].Centroid.size(); j++)
            tmp += pow((Element[j] - data[i].Centroid[j]), 2);
        tmp = sqrt(tmp);
        if (tmp<min)
        {
            min = tmp;
            indexMinCluster = i;
        }
        tmp=0;
    }
    return indexMinCluster;
}

vector<Cluster> General_K_means(Cluster data, size_t AmountCluster)
{
    vector<Cluster> Clusters(AmountCluster); // массив в котором хранятся все кластеры
    int iter = 0;
    int index;
    for (size_t i = 0; i < Clusters.size(); i++)
        Clusters[i].Centroid = data.Elements[rand() % data.Elements.size()];
    while(true)
    {
        iter++;
        for (size_t i = 0; i<data.Elements.size(); i++)
        {
            index = ClusterAffiliation(data.Elements[i], Clusters);
            Clusters[index].Elements.push_back(data.Elements[i]);
            RecalculateCentroids(Clusters[index]);
        }
        if(iter==20)
            break;
        for (size_t i = 0; i<Clusters.size(); i++)
        {
            while (Clusters[i].Elements.size() != 0)
                Clusters[i].Elements.pop_back();
        }
    }
    return Clusters;
}
