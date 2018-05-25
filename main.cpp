#include "clusterclass.h"
#include "minspanningtree.h"

using namespace std;

void MoveElement(ClusterClass &C1, ClusterClass &C2, int indexElement)
{
    C2.Elements.push_back(C1.Elements[indexElement]);
    C1.Elements.erase(C1.Elements.begin() + indexElement - 1);
}

int main()
{
    int n,m, k;
    ifstream mat("in.txt");
    mat >> n;
    mat >> m;
    mat >> k;
    ClusterClass GeneralCluster(n,m);
    for(int i=0; i<n; i++)
        for (int j=0; j<m; j++)
            mat >> GeneralCluster[i][j];
    MinSpanningTree MST;
    MST.General_MST(GeneralCluster);
//    cout << GeneralCluster<< endl;
//    K_Means KM;
//    vector<ClusterClass> Test = KM.General_K_means(GeneralCluster, k);

//    for (size_t i = 0; i < Test.size(); i++)
//    {
//        cout << "Cluster № " << i << endl;
//        cout << Test[i] << endl;
//    }
    return 0;
}
