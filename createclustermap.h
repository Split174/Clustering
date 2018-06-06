#include <cluster.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>
const int width = 800;
const int height = 640;

void SetRandomColor(vector<char>& Color)
{
    Color[0] = rand() % 256;
    Color[1] = rand() % 256;
    Color[2] = rand() % 256;
}

void SetPoint(char*& dataPoint, uint x, uint y, vector<char> Color, int sizePoint = 1)
{
    for (int i = 0; i < sizePoint; i++)
        for (int j = 0; j < sizePoint; j++)
        {
             dataPoint[(y+i)*width*3 + (x+j)*3 + 0] = Color[0];
             dataPoint[(y+i)*width*3 + (x+j)*3 + 1] = Color[1];
             dataPoint[(y+i)*width*3 + (x+j)*3 + 2] = Color[2];
        }
}

void DrawCluster(Cluster Source, vector<char> Color, char*& dataPoint)
{
    size_t AmountElementCluster = Source.Elements.size();
    for (size_t i = 0; i < AmountElementCluster; i++)
    {
        SetPoint(dataPoint, Source.Elements[i][0], Source.Elements[i][1], Color, 2);
    }
}

void CreatePng(vector<Cluster> dataClusters, string file)
{
    char * dataPoint = (char*) malloc(width*height*3);
    for (int i = 0; i < width*height*3; i++)
        dataPoint[i] = 0;
    int AmountCluster = dataClusters.size();
    vector<char> ColorCluster(3);
    for (int i = 0; i < AmountCluster; i++)
    {
        SetRandomColor(ColorCluster);
        DrawCluster(dataClusters[i], ColorCluster, dataPoint);
    }
    if (file == "MST.png")
        stbi_write_png("MST.png", width, height, 3, dataPoint, 0);
    else
        stbi_write_png("Kmeans.png", width, height, 3, dataPoint, 0);
}
