#include "cluster.h"

double AverageDistanceInsideCluster(Cluster data)
{
    size_t AmountElementsInCluster = data.Elements.size();
    if (AmountElementsInCluster == 1) // иначе будет NAN
        return 0;
    double DistanceInsideCluster = 0;
    int AmountSum = 0;
    for (size_t i = 0; i < AmountElementsInCluster; i++)
        for (size_t j = i+1; j < AmountElementsInCluster; j++)
        {
            DistanceInsideCluster += DistanceFormObjToObj(data.Elements[i], data.Elements[j]);
            AmountSum++;
        }
    return (DistanceInsideCluster / AmountSum);
}

double AverageDistanceInsideAllCluster(vector<Cluster> data)
{
    size_t AmountCluster = data.size();
    double Res = 0;
    for (size_t i = 0; i < AmountCluster; i++)
        Res += (AverageDistanceInsideCluster(data[i]));
    return ( Res / AmountCluster);
}

double AverageDistanceBetweenClusters(vector<Cluster> data)
{
    size_t AmountClusters = data.size();
    double DistanceBetweenClusters = 0;
    int AmountSum = 0;
    for (size_t i = 0; i < AmountClusters; i++)
        for (size_t j = i+1; j < AmountClusters; j++)
        {
            DistanceBetweenClusters += DistanceFormObjToObj(data[i].Centroid, data[j].Centroid);
            AmountSum++;
        }
    return (DistanceBetweenClusters / (AmountSum));
}

double ClusteringAccuracy(vector<Cluster> data)
{
    //int AmountCluster = data.size();
    return ((AverageDistanceInsideAllCluster(data)) / AverageDistanceBetweenClusters(data));
}
