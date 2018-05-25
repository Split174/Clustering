#include "clusterclass.h"

using namespace std;

int ClusterAffiliation(vector<double> Element, vector<ClusterClass> Cls)
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

void MoveElement(ClusterClass &C1, ClusterClass &C2, int indexElement)
{
    C2.Elements.push_back(C1.Elements[indexElement]);
    C1.Elements.erase(C1.Elements.begin() + indexElement - 1);
}

vector<ClusterClass> K_Means(ClusterClass Cl, int sizeK)
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



int main()
{
    int n,m, k;
    ifstream mat("in.txt");
    mat >> n;
    mat >> m;
    //mat >> k;
    ClusterClass GeneralCluster(n,m);
    for(int i=0; i<n; i++)
        for (int j=0; j<m; j++)
            mat >> GeneralCluster[i][j];

//    int n,m, k;
//    ifstream mat("mat.txt");
//    mat >> n;
//    mat >> m;
//    mat >> k;
//    ClusterClass GeneralCluster(n,m);
//    for(int i=0; i<n; i++)
//        for (int j=0; j<m; j++)
//            mat >> GeneralCluster[i][j];
    GeneralCluster.CalcDistance(); // высчитывание матрицы дистанции и вывод её для дебага( оно же матрица смежности для графа )
    double R = GeneralCluster.getR();
    cout << "R = " << R << endl; // высчитывание потенциального "расстояния для удаления"

    for (size_t i = 0; i < GeneralCluster.Distance.size(); i++)
    {
        for (size_t j = 0; j < GeneralCluster.Distance[i].size(); j++)
            cout << GeneralCluster.Distance[i][j] << "\t";
        cout << endl;
    }

    vector<int> N;

    N = GeneralCluster.GetMinimalTree(); // передаём по ссылке для дальнейшего использования
    GeneralCluster.DeleteBigEdge(N, R);
    GeneralCluster.ClusterMinimalTree();

//    cout << GeneralCluster<< endl;
//    vector<ClusterClass> Test = K_Means(GeneralCluster, k);

//    for (size_t i = 0; i < Test.size(); i++)
//    {
//        cout << "Cluster № " << i << endl;
//        cout << Test[i] << endl;
//    }
    return 0;
}
