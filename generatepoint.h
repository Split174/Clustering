#ifndef GENERATEPOINT_H
#define GENERATEPOINT_H
#include <fstream>
#include "math.h"
#include <vector>
#include <time.h>
using namespace std;

struct Point
{
    int x,y;
    Point(int _x=0, int _y=0)
    {
        x = _x;
        y = _y;
    }
};

void GenerateCenter(vector<Point>& Pcenter, int R)
{
    for (size_t i = 0; i < Pcenter.size(); i++)
    {
        Pcenter[i].x = R + (rand()%(800-R));
        Pcenter[i].y = R + (rand()%(640-R));
    }
}
void GeneratePoint(int R, int AmountPoint)
{
    srand( time(0) );
    ofstream fout("in.txt");
    int AmountBundle = 2+ (rand() % 50);
    vector<Point> Pcenter(AmountBundle);
    GenerateCenter(Pcenter, R);
    fout << AmountPoint << " " << 2 << " " << endl;
    for (int i = 0; i < AmountPoint; i++)
    {
        int randPointIndex = rand() % AmountBundle;
        fout << Pcenter[randPointIndex].x + (-R + (rand() % R)) << " "
                << Pcenter[randPointIndex].y + (-R + (rand() % R)) << endl;
    }
    fout.close(); // закрываем файл
}
#endif // GENERATEPOINT_H
