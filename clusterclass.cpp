#include "clusterclass.h"

double DistanceFormObjToObj(vector<double> Obj1, vector<double> Obj2)
{
    double res = 0;
    for (size_t i = 0; i < Obj1.size(); i++)
        res += pow(Obj1[i] - Obj2[i], 2);
    res = sqrt(res);
    return res;
}

void ClusterClass::CalcDistance()
{
    vector<vector<double>> Res(this->Elements.size(), vector<double>(this->Elements.size()));
    for (size_t i = 0; i < this->Elements.size() - 1; i++)
        for (size_t j = i+1; j < this->Elements.size(); j++)
            if (i == j)
                Res[i][j] = 0;
            else
            {
                Res[i][j] += DistanceFormObjToObj(this->Elements[i], this->Elements[j]);
                Res[j][i] = Res[i][j];
            }
    this->Distance = Res;
}

vector<int> ClusterClass::GetMinimalTree()
{
    int n = this->Distance.size();
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
            if (this->Distance[v][to] < min_e[to]) {
                min_e[to] = this->Distance[v][to];
                sel_e[to] = v;
            }
    }

    return Res;
}

double ClusterClass::getR()
{
    int k = 0;
    double res=0;
    for (size_t i = 0; i<this->Distance.size(); i++)
        for (size_t j = i; j<this->Distance[i].size(); j++)
        {
            if (i == j)
                continue;
            res += this->Distance[i][j];
            k++;
        }
    return (res/k)*0.5;
}

void ClusterClass::DeleteBigEdge(vector<int> Neighbor, double R)
{
    vector<vector<double>> tmp(Neighbor.size(), vector<double>(Neighbor.size()));
    for (size_t i = 0; i < Neighbor.size(); i++)
    {
        if (Neighbor[i] == -1)
            continue;
        tmp[i][Neighbor[i]] = this->Distance[i][Neighbor[i]];
        tmp[Neighbor[i]][i] = this->Distance[Neighbor[i]][i];
    }

    this->Distance = tmp;

    for (size_t i = 0; i < Neighbor.size(); i++)
    {
        if (Neighbor[i] == -1)
            continue;
        if (this->Distance[i][Neighbor[i]] >= R )
        {
            this->Distance[i][Neighbor[i]] = 0; // TODO оптимизацию плеееез бегает по всей матрице
            this->Distance[Neighbor[i]][i] = 0;
        }
    }

    for (size_t i = 0; i < this->Distance.size(); i++)
    {
        for (size_t j = 0; j < this->Distance[i].size(); j++)
            cout << this->Distance[i][j] << "\t";
        cout << endl;
    }
}

void ClusterClass::ClusterMinimalTree()
{
    vector<vector<double>> a = this->Distance;
    int n = this->Distance.size(), cur = 0;
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
              was[v] = cur;
              for (int j = 0; j < n; j++)
                  if (a[v][j] != 0.0 && was[j] == -1)
                     q.push(j);
        }
        cur++;
    }
    for (size_t i = 0; i < was.size(); i++)
        cout << "Object : " << i << " in " << was[i] << " cluster" << endl;
}

ClusterClass::ClusterClass()
{
    //NumOfObject = 1;
    //cout << "construct";
    //Elements = vector<vector<double>>(NumOfObject, vector <double>(1));
}

ClusterClass::ClusterClass(int _NumberOfObject, int _NumberOfVariables)
{
    //NumOfObject = _NumberOfObject;
    Elements = vector<vector<double>>(_NumberOfObject, vector <double>(_NumberOfVariables));
}

void ClusterClass::RecalculateCentroids() // пересчитывает центройду
{
    //cout << "RecalculateCentroids " << endl;
        int totalInCluster = 0;
        vector<double> tmp(this->Centroid.size(), 0); // инициализируем вектор для дальнейшего его присваивания к центройде
        // надо для пересчитывания центройды, ибо занулять текущую лень, проще переприсвоить
        for (size_t i = 0; i < this->Elements.size(); i++)
        {
            for (size_t j = 0; j< this->Elements[i].size(); j++)
                tmp[j] += this->Elements[i][j];
            totalInCluster++;
        }
        if (totalInCluster > 0)
        {
            for (size_t i = 0; i< tmp.size(); i++)
                tmp[i] /= totalInCluster;
            this->Centroid = tmp;
        }
        //for (size_t i = 0; i< this->Centroid.size(); i++)
        //{
            //cout << this->Centroid[i] << " ";
        //}
        //cout <<endl;
}

vector<double>&  ClusterClass::operator[](int row)
{
    return Elements[row];
}

ostream& operator <<(ostream &os, ClusterClass &C)
{
    os << "Cluster Centroid: ";
    for (size_t i = 0; i < C.Centroid.size(); i++)
        os << C.Centroid[i] << " ";
    os << endl;
    for (size_t i = 0; i < C.Elements.size(); i++) // Elements.size() вернёт количество объектов
    {
        os << "Element № " << i << endl;
        for (size_t j = 0; j < C.Elements[i].size(); j++) // C.Elements[i].size() вернёт количество параметров i-го объекта
            os << C[i][j] << '\t';
        os << endl;
    }
    return os;
}
