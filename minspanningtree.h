#include <cluster.h>
#include <generalfunc.h>
vector<int> GetMinimalTree(vector<vector<double>> Distance)
{
    int n = Distance.size();
    int INF = 1000000000;

    vector<bool> used (n);
    vector<int> sel_e (n, -1);
    vector<double> min_e (n, INF);
    vector<int> Res = sel_e;

    min_e[0] = 0;
    for (int i=0; i<n; ++i) {
        int v = -1;
        for (int j=0; j<n; ++j)
            if (!used[j] && (v == -1 || min_e[j] < min_e[v]))
                v = j;
        if (min_e[v] == INF) {
            cout << "No MST!";
            exit(0);
        }

        used[v] = true;
        if (sel_e[v] != -1)
        {
            //cout << v << " " << sel_e[v] << endl;
            Res[v] = sel_e[v];
        }

        for (int to=0; to<n; ++to)
            if (Distance[v][to] < min_e[to]) {
                min_e[to] = Distance[v][to];
                sel_e[to] = v;
            }
    }

    return Res;
}

void DeleteBigEdgeInTree(vector<vector<double> >& Distance, vector<int> Neighbor, double Weight)
{
    vector<vector<double>> tmp(Neighbor.size(), vector<double>(Neighbor.size()));
    for (size_t i = 0; i < Neighbor.size(); i++)
    {
        if (Neighbor[i] == -1)
            continue;
        tmp[i][Neighbor[i]] = Distance[i][Neighbor[i]];
        tmp[Neighbor[i]][i] = Distance[Neighbor[i]][i];
    }

    Distance = tmp;

    for (size_t i = 0; i < Neighbor.size(); i++)
    {
        if (Neighbor[i] == -1)
            continue;
        if (Distance[i][Neighbor[i]] >= Weight )
        {
            Distance[i][Neighbor[i]] = 0; // TODO оптимизацию плеееез бегает по всей матрице
            Distance[Neighbor[i]][i] = 0;
        }
    }
}

vector<int> AmountComponentsAndAffiliationElements(vector<vector<double>> Distance, int& AmountCluster)
{
    vector<vector<double>> a = Distance;
    int n = Distance.size();
    vector<int> was(n, -1);
    queue<int> q;
    for (int i = 0; i < n; i++)
    {
        if (was[i] != -1)
           continue;
        q.push(i);
        while (!q.empty())
        {
              int v = q.front();
              q.pop();
              if (was[v] != -1)
                 continue;
              was[v] = AmountCluster;
              for (int j = 0; j < n; j++)
                  if (a[v][j] != 0.0 && was[j] == -1)
                     q.push(j);
        }
        AmountCluster++;
    }
    return was;
}

vector<Cluster> AppendElementsClusters(vector<int> ClusterAffiliation,
                                                             Cluster Source, int AmountCluster)
{
    vector<Cluster> Res(AmountCluster);
    for (size_t i = 0; i < ClusterAffiliation.size(); i++)
        Res[ClusterAffiliation[i]].Elements.push_back(Source.Elements[i]);
    return Res;
}

//double GetDist(vector<vector<double>> Distance, vector<int> Neighbor)
//{
//    double Res = 0;
//    double max = -1;
//    for (size_t i = 0; i < Neighbor.size(); i++)
//    {
//        if (Neighbor[i] == -1)
//            continue;
//        if (Distance[i][Neighbor[i]] > max)
//            max = Distance[i][Neighbor[i]];
//        Res += Distance[i][Neighbor[i]];
//    }
//    return (Res/max);
//}

double GetMaxBranch(vector<vector<double>> Distance, vector<int> Neighbor)
{
    double max = -1;
    for (size_t i = 0; i < Neighbor.size(); i++)
    {
        if (Neighbor[i] == -1)
            continue;
        if (Distance[i][Neighbor[i]] > max)
            max = Distance[i][Neighbor[i]];
    }
    return max;
}

vector<Cluster> MST_Method(Cluster& dataElement)
{
    CalcDistance(dataElement);
    vector<vector<double>> matrixDistance = dataElement.Distance; // фикс диструктивности алгоритма
    vector<int> N;
    vector<int> ClusterAffiliation;
    int AmountCluster = 0;
    N = GetMinimalTree(matrixDistance);
    double MaxBranch = GetMaxBranch(matrixDistance, N);
    cout << "MaxBranch  =" << MaxBranch  << endl;
    DeleteBigEdgeInTree(matrixDistance, N, MaxBranch * 0.35);
    ClusterAffiliation = AmountComponentsAndAffiliationElements(matrixDistance, AmountCluster);
    vector<Cluster> Res = AppendElementsClusters(ClusterAffiliation, dataElement, AmountCluster);
    return Res;
}
