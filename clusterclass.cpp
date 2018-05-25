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
