#include "utils.h"

vector<MandelbrotElement> *CalculateMandelbrot(float gridWidth, float gridHeight, float stepsis)
{
    int xMax = (int) (gridWidth / stepsis);
    int yMax = (int) (gridHeight / stepsis);

    static vector<MandelbrotElement> points;

    for( auto i = 0; i < xMax; i++)
    {
        for( auto j = 0; j < yMax; j++ )
        {
            points.push_back(MandelbrotElement(i * stepsis - gridWidth / 2, j * stepsis - gridHeight / 2));
        }
    }

    return &points;
}

void DisplaySet(vector<MandelbrotElement> *points, float gridWidth, float gridHeight, int consWidth, int consHeight)
{
    int pointsCount = points->size();

    for( auto i = 0; i < pointsCount; i++ )
    {
        MandelbrotElement point = points->at(i);

        int consX = (int) (point.x * consWidth / gridWidth); 
        int consY = (int) (point.y * consHeight / gridHeight); 

        SetConsoleXY(consX, consY);

        if( point.outside )
        {
            cout << ' ';
        }
        else
        {
            cout << '*';
        }        
    }

    SetConsoleXY(0, 0);
}

int main()
{
    const float gridWidth = 2.5f;
    const float gridHeight = 2.0f;

    vector<MandelbrotElement> *points = CalculateMandelbrot(gridWidth, gridHeight, 0.02f);

    int oldConWidth = 0, oldConHeight = 0;

    while( true )
    {
        int newConWidth, newConHeight;
        GetConsoleSize(newConWidth, newConHeight);

        if( newConWidth != oldConWidth || newConHeight != oldConHeight )
        {
            system("CLS");

            DisplaySet(points, gridWidth, gridHeight, newConWidth, newConHeight);

            oldConWidth = newConWidth;
            oldConHeight = newConHeight;
        }
    }

    cin.ignore();
    return 0;
}