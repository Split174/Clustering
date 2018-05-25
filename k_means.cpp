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
//    cout << "touch Element :";
//    for (size_t i = 0; i < Element.size(); i++)
//        cout << Element[i] << " ";
//    cout << endl;
    return indexMinCluster;
}

vector<ClusterClass> K_Means::General_K_means(ClusterClass Cl, int sizeK)
{
    vector<ClusterClass> Clusters(sizeK); // массив в котором хранятся все кластеры
    int WTF = 0;
    int index;
    for (size_t i = 0; i < Clusters.size(); i++)
        Clusters[i].Centroid = Cl.Elements[rand() % Cl.Elements.size()];
//    Clusters[0].Centroid = Cl.Elements[0];
//    Clusters[1].Centroid = Cl.Elements[3];
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
    //cout << "size Clu " << Clusters.size() << endl;
//       while(WTF!=3)
//    {
//        for (size_t i = 0; i<Clusters.size(); i++)
//            for (int j = 0; j < Clusters.Elements.size(); j++)
//                {
//                    index = ClusterAffiliation(Cl.Elements[i], Clusters);
//                    if(index == i)
//                        continue;
//                    else
//                        w
//                }
//        for (size_t i = 0; i<Clusters.size(); i++)
//            Clusters[i].RecalculateCentroids();
//        WTF++;
//    }
    return Clusters;
}

K_Means::K_Means()
{

}
