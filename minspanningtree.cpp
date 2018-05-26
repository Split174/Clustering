#include "minspanningtree.h"

MinSpanningTree::MinSpanningTree()
{

}

vector<int> MinSpanningTree::GetMinimalTree(ClusterClass C)
{
    int n = C.Distance.size();
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
            cout << v << " " << sel_e[v] << endl;
            Res[v] = sel_e[v];
        }

        for (int to=0; to<n; ++to)
            if (C.Distance[v][to] < min_e[to]) {
                min_e[to] = C.Distance[v][to];
                sel_e[to] = v;
            }
    }

    return Res;
}

double MinSpanningTree::getR(ClusterClass C)
{
    int k = 0;
    double res=0;
    for (size_t i = 0; i<C.Distance.size(); i++)
        for (size_t j = i; j<C.Distance[i].size(); j++)
        {
            if (i == j)
                continue;
            res += C.Distance[i][j];
            k++;
        }
    return (res/k)*0.5;
}

void MinSpanningTree::DeleteBigEdge(ClusterClass& C, vector<int> Neighbor, double R)
{
    vector<vector<double>> tmp(Neighbor.size(), vector<double>(Neighbor.size()));
    for (size_t i = 0; i < Neighbor.size(); i++)
    {
        if (Neighbor[i] == -1)
            continue;
        tmp[i][Neighbor[i]] = C.Distance[i][Neighbor[i]];
        tmp[Neighbor[i]][i] = C.Distance[Neighbor[i]][i];
    }

    C.Distance = tmp;

    for (size_t i = 0; i < Neighbor.size(); i++)
    {
        if (Neighbor[i] == -1)
            continue;
        if (C.Distance[i][Neighbor[i]] >= R )
        {
            C.Distance[i][Neighbor[i]] = 0; // TODO оптимизацию плеееез бегает по всей матрице
            C.Distance[Neighbor[i]][i] = 0;
        }
    }

    for (size_t i = 0; i < C.Distance.size(); i++)
    {
        for (size_t j = 0; j < C.Distance[i].size(); j++)
            cout << C.Distance[i][j] << "\t";
        cout << endl;
    }
}

vector<int> MinSpanningTree::AmountComponentsAndAffiliationElements(ClusterClass C, int& AmountCluster)
{
    vector<vector<double>> a = C.Distance;
    int n = C.Distance.size();
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



vector<ClusterClass> MinSpanningTree::MST_Method(ClusterClass Cl)
{
    vector<ClusterClass> ClusterSet;
    Cl.CalcDistance(); // высчитывание матрицы дистанции и вывод её для дебага( оно же матрица смежности для графа )
    double R = this->getR(Cl);
    cout << "R = " << R << endl; // высчитывание потенциального "расстояния для удаления"

//    for (size_t i = 0; i < Cl.Distance.size(); i++)
//    {
//        for (size_t j = 0; j < Cl.Distance[i].size(); j++)
//            cout << Cl.Distance[i][j] << "\t";
//        cout << endl;
//    }

    vector<int> N;
    vector<int> ClusterAffiliation;
    int AmountCluster = 0;
    N = this->GetMinimalTree(Cl);
    this->DeleteBigEdge(Cl, N, R);
    ClusterAffiliation = this->AmountComponentsAndAffiliationElements(Cl, AmountCluster);
    ClusterSet = this->AppendElementsClusters(ClusterAffiliation, Cl, AmountCluster);

    return ClusterSet;
}
