#ifndef CHANGEFUNCTIONS_H
#define CHANGEFUNCTIONS_H

#include <cluster.h>

double DistanceFormObjToObj(vector<double> Obj1, vector<double> Obj2)
{
    double res = 0;
    for (size_t i = 0; i < Obj1.size(); i++)
        res += pow(Obj1[i] - Obj2[i], 2);
    res = sqrt(res);
    if (res == 0)
        res = 0.0000001; // костыль, на случай если есть элементы с одинаковыми параметрами
    return res;
}

void CalcDistance(Cluster& data)
{
    vector<vector<double>> Res(data.Elements.size(), vector<double>(data.Elements.size()));
    for (size_t i = 0; i < data.Elements.size() - 1; i++)
        for (size_t j = i+1; j < data.Elements.size(); j++)
            if (i == j)
                Res[i][j] = 0;
            else
            {
                Res[i][j] += DistanceFormObjToObj(data.Elements[i], data.Elements[j]);
                Res[j][i] = Res[i][j];
            }
    data.Distance = Res;
}

void RecalculateCentroids(Cluster& data)
{
    //cout << "RecalculateCentroids " << endl;
        int totalInCluster = 0;
        vector<double> tmp(data.Elements[0].size(), 0); // инициализируем вектор для дальнейшего его присваивания к центройде
        // надо для пересчитывания центройды, ибо занулять текущую лень, проще переприсвоить
        for (size_t i = 0; i < data.Elements.size(); i++)
        {
            for (size_t j = 0; j< data.Elements[i].size(); j++)
                tmp[j] += data.Elements[i][j];
            totalInCluster++;
        }
        if (totalInCluster > 0)
        {
            for (size_t i = 0; i< tmp.size(); i++)
                tmp[i] /= totalInCluster;
            data.Centroid = tmp;
        }
}

ostream& operator <<(ostream &os, Cluster &data)
{
    os << "Cluster Centroid: ";
    for (size_t i = 0; i < data.Centroid.size(); i++)
        os << data.Centroid[i] << " ";
    os << endl;
    for (size_t i = 0; i < data.Elements.size(); i++)
    {
        os << "Element № " << i << endl;
        for (size_t j = 0; j < data.Elements[i].size(); j++)
            os << data.Elements[i][j] << '\t';
        os << endl;
    }
    return os;
}

#endif // CHANGEFUNCTIONS_H
