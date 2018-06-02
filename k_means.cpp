#include "k_means.h"

int K_Means::ClusterAffiliation(vector<double> Element, vector<ClusterClass> Cls)
{
    //cout << "ClusterAffiliation" << endl;
    int indexMinCluster;
    double min = 99999;
    double tmp=0;
    for (size_t i = 0; i < Cls.size(); i++)
    {
        for (size_t j = 0; j < Cls[i].Centroid.size(); j++)
            tmp += pow((Element[j] - Cls[i].Centroid[j]), 2);
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

vector<ClusterClass> K_Means::General_K_means(ClusterClass Cl, int sizeK)
{
    vector<ClusterClass> Clusters(sizeK); // массив в котором хранятся все кластеры
    int WTF = 0;
    int index;
    for (size_t i = 0; i < Clusters.size(); i++)
        Clusters[i].Centroid = Cl.Elements[rand() % Cl.Elements.size()];
    while(true)
    {
        WTF++;
        for (size_t i = 0; i<Cl.Elements.size(); i++)
        {
            index = ClusterAffiliation(Cl.Elements[i], Clusters);
            Clusters[index].Elements.push_back(Cl.Elements[i]);
            Clusters[index].RecalculateCentroids();
        }
        if(WTF==20)
            break;
        for (size_t i = 0; i<Clusters.size(); i++)
        {
            while (Clusters[i].Elements.size() != 0)
                Clusters[i].Elements.pop_back();
        }
    }
    return Clusters;
}

K_Means::K_Means()
{

}
