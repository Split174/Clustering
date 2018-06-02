#include "minspanningtree.h"

MinSpanningTree::MinSpanningTree()
{

}

vector<int> MinSpanningTree::GetMinimalTree(vector<vector<double>> Distance)
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

double MinSpanningTree::getR(vector<vector<double>> Distance)
{
    int AmountPoint = Distance.size();
    int k = 0;
    double res=0;
    for (size_t i = 0; i<Distance.size(); i++)
        for (size_t j = i+ 1; j<Distance[i].size(); j++)
        {
            if (i == j)
                continue;
            res += Distance[i][j];
        }
    return (res/(AmountPoint*AmountPoint));
}

void MinSpanningTree::DeleteBigEdgeInTree(vector<vector<double> >& Distance, vector<int> Neighbor, double R)
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
        if (Distance[i][Neighbor[i]] >= R )
        {
            Distance[i][Neighbor[i]] = 0; // TODO оптимизацию плеееез бегает по всей матрице
            Distance[Neighbor[i]][i] = 0;
        }
    }
}

vector<int> MinSpanningTree::AmountComponentsAndAffiliationElements(vector<vector<double>> Distance, int& AmountCluster)
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

vector<ClusterClass> MinSpanningTree::AppendElementsClusters(vector<int> ClusterAffiliation,
                                                             ClusterClass Source, int AmountCluster)
{
    vector<ClusterClass> Res(AmountCluster);
    for (size_t i = 0; i < ClusterAffiliation.size(); i++)
        Res[ClusterAffiliation[i]].Elements.push_back(Source.Elements[i]);
    return Res;
}

double GetDist(vector<vector<double>> Distance, vector<int> Neighbor)
{
    double Res = 0;
    double max = -1;
    for (size_t i = 0; i < Neighbor.size(); i++)
    {
        if (Neighbor[i] == -1)
            continue;
        if (Distance[i][Neighbor[i]] > max)
            max = Distance[i][Neighbor[i]];
        Res += Distance[i][Neighbor[i]];
    }
    return (Res/max);
}

double GetMaxDivideTwo(vector<vector<double>> Distance, vector<int> Neighbor)
{
    double max = -1;
    for (size_t i = 0; i < Neighbor.size(); i++)
    {
        if (Neighbor[i] == -1)
            continue;
        if (Distance[i][Neighbor[i]] > max)
            max = Distance[i][Neighbor[i]];
    }
    return (max/2);
}

vector<ClusterClass> MinSpanningTree::MST_Method(ClusterClass dataElement)
{
    vector<ClusterClass> ClusterSet;
    dataElement.CalcDistance(); // высчитывание матрицы дистанции и вывод её для дебага( оно же матрица смежности для графа )
    vector<vector<double>> matrixDistance = dataElement.Distance; // фикс диструктивности алгоритма
    double OptimalDistance = this->getR(matrixDistance);
    cout << "OptimalDistance = " << OptimalDistance << endl;
    vector<int> N;
    vector<int> ClusterAffiliation;
    int AmountCluster = 0;
    N = this->GetMinimalTree(matrixDistance);
    double Dist = GetDist(matrixDistance, N);
    cout << "Dist =" << Dist << endl;
    //Dist = abs(Dist - OptimalDistance);
    double MaxDivideTwo = GetMaxDivideTwo(matrixDistance, N);
    cout << "Max =" << MaxDivideTwo << endl;
    this->DeleteBigEdgeInTree(matrixDistance, N, MaxDivideTwo);
    ClusterAffiliation = this->AmountComponentsAndAffiliationElements(matrixDistance, AmountCluster);
    ClusterSet = this->AppendElementsClusters(ClusterAffiliation, dataElement, AmountCluster);
    return ClusterSet;
}
