#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <memory>
#include "Point.h"
#include "Map.h"

using namespace std;

int totalPoints = 0;
vector<Point> points;
unique_ptr<Map> map;
double H = 0.0;

int main()
{
    cout << "Enter total points: ";
    cin >> totalPoints;
    for(int i = 0, x, y; i < totalPoints; i++)
    {
        cout << "(x" << i+1 << ", y" << i+1 << ") = ";
        cin >> x >> y;
        points.emplace_back(x, y);
    }
    map = make_unique<Map>(points);
    map->initializeMap();
    map->doCycle(H);
    map->doCycle(H);
    map->doCycle(H);
    map->doCycle(H);
    return 0;
}