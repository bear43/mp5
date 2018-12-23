//
// Created by kostya on 23.12.18.
//

#ifndef UNTITLED_MAP_H
#define UNTITLED_MAP_H

#define MAX_ELEMENTS 30 //nxn

#define forin(start, n) for(int i = start; i < n; i++)
#define forjn(start, n) for(int j = start; j < n; j++)

#include <vector>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <limits>
#include <array>
#include <fmt/format.h>
#include "Point.h"


using namespace std;

class Map : public Object
{
private:
    array<double[MAX_ELEMENTS], MAX_ELEMENTS> map,
                                            savedMap,
                                            exchangedMap,
                                            reducedMap,
                                            nonreducedMap;
    array<double, MAX_ELEMENTS> minimalMapRow, minimalMapColumn;
    int size, reducedSize, nonReducedSize;
    vector<Point> &points;
    double getMinElementInRow(int rowNum);
    double getMinElementInColumn(int columnNum);
    void subtractInRow(int rowNum, double value);
    void subtractInColumn(int columnNum, double value);
    void saveMap(array<double[MAX_ELEMENTS], MAX_ELEMENTS>& map);
    void restoreMap(array<double[MAX_ELEMENTS], MAX_ELEMENTS>& from);
public:
    Map(vector<Point> &points);
    void clearMinimalMapRow();
    void clearMinimalMapColumn();
    double reduceRows(bool reduce);
    double reduceColumns(bool reduce);
    void fillMinimalMaps();
    void setMapValue(int i, int j, double value);
    void setMapValue(Point &point, double value);
    void nullExchange();
    Point getExchangeSum();
    void clearMinimalMaps();
    void initializeMap();
    string toString() override;
    bool equals(Object &obj) override;
    double getH();
    double getHWithoutReduce();
    double getNumFromExchangeMap(int i, int j);
    void deleteRowAndColumn(int rowNum, int columnNum);
    void saveAsReduced();
    void saveAsNonReduced();
    void restoreReduced();
    void restoreNonReduced();
    void doCycle(double& H);
    void clearExchangeMap();
};


#endif //UNTITLED_MAP_H
