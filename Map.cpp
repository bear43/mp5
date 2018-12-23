//
// Created by kostya on 23.12.18.
//

#include "Map.h"

Map::Map(vector<Point> &points) : points(points)
{
    size = (int)points.size();
}

void Map::initializeMap()
{
    forin(1, size+1)
    {
        map[0][i] = i;
        map[i][0] = i;
    }
    forin(1, size+1)
    {
        forjn(1, size+1)
        {
            if(i != j)
                map[i][j] = sqrt((pow(abs(points[i].x-points[j].x), 2)+pow(abs(points[i].y-points[j].y), 2)));
            else
                map[i][j] = -1;
        }
    }
}

string Map::toString()
{
    stringstream ss;
    forin(0, size+1)
    {
        forjn(0, size+1)
        {
            if(i == 0)
                ss << fmt::format("{0:.1f}   ", map[i][j]);
            else
                ss << fmt::format("{0:.1f}  ", map[i][j]);
        }
        ss << endl;
    }
    return ss.str();
}

double Map::getMinElementInRow(int rowNum)
{
    double _min = INT32_MAX;
    forin(1, size+1)
    {
        if(map[rowNum][i] != -1)
            _min = min(map[rowNum][i], _min);
    }
    return _min;
}

double Map::getMinElementInColumn(int columnNum)
{
    double _min = INT32_MAX;
    forin(1, size+1)
    {
        if(map[i][columnNum] != -1)
            _min = min(map[i][columnNum], _min);
    }
    return _min;
}

double Map::getH()
{
    double H = 0.0;
    H += reduceRows(true) + reduceColumns(true);
    return H;
}

double Map::getHWithoutReduce()
{
    double H = 0.0;
    H += reduceRows(false) + reduceColumns(false);
    return H;
}

void Map::subtractInRow(int rowNum, double value)
{
    forin(1, size+1)
        if(map[rowNum][i] != -1)
            map[rowNum][i] = map[rowNum][i]-value;
}

void Map::subtractInColumn(int columnNum, double value)
{
    forin(1, size+1)
        if(map[i][columnNum] != -1)
            map[i][columnNum] = map[i][columnNum]-value;
}

void Map::clearMinimalMapRow()
{
    forin(0, MAX_ELEMENTS)
        minimalMapRow[i] = 0;
}

void Map::clearMinimalMapColumn()
{
    forin(0, MAX_ELEMENTS)
        minimalMapColumn[i] = 0;
}

void Map::fillMinimalMaps()
{
    forin(1, size+1)
    {
        minimalMapRow[i] = getMinElementInRow(i);
        minimalMapColumn[i] = getMinElementInColumn(i);
    }
}

void Map::saveMap(array<double[MAX_ELEMENTS], MAX_ELEMENTS>& map)
{
    forin(0, MAX_ELEMENTS)
        forjn(0, MAX_ELEMENTS)
        {
            map[i][j] = this->map[i][j];
        }
}

void Map::restoreMap(array<double[MAX_ELEMENTS], MAX_ELEMENTS>& from)
{
    forin(0, MAX_ELEMENTS)
        forjn(0, MAX_ELEMENTS)
            map[i][j] = from[i][j];
}

void Map::nullExchange()
{
    clearMinimalMaps();
    clearExchangeMap();
    double a, b;
    forin(1, size+1)
    {
        forjn(1, size + 1)
        {
            if (map[i][j] == 0)
            {
                map[i][j] = -1;
                a = getMinElementInRow(i);
                b = getMinElementInColumn(j);
                exchangedMap[i][j] = a+b;
                map[i][j] = 0;
            }
        }
    }
}

double Map::getNumFromExchangeMap(int i, int j)
{
    return exchangedMap[i][j];
}

void Map::clearMinimalMaps()
{
    clearMinimalMapRow();
    clearMinimalMapColumn();
}

Point Map::getExchangeSum()
{
    int maxi = -1, maxj = -1;
    double sum = 0.0;
    forin(1, size+1)
    {
        forjn(1, size + 1)
        {
            if (exchangedMap[i][j] != 0)
            {
                if (maxi == -1 && maxj == -1)
                {
                    maxi = i;
                    maxj = j;
                } else
                {
                    if (exchangedMap[maxi][maxj] < exchangedMap[i][j])
                    {
                        maxi = i;
                        maxj = j;
                    }
                    sum += exchangedMap[i][j];
                }
            }
        }
    }
    return { maxi, maxj };
}

void Map::setMapValue(int i, int j, double value)
{
    map[i][j] = value;
}

void Map::setMapValue(Point &point, double value)
{
    setMapValue(point.x, point.y, value);
}

double Map::reduceRows(bool reduce)
{
    double H = 0.0;
    forin(1, size+1)
    {
        minimalMapRow[i] = getMinElementInRow(i);
        H += minimalMapRow[i];
        if(reduce) subtractInRow(i, minimalMapRow[i]);
    }
    return H;
}

double Map::reduceColumns(bool reduce)
{
    double H = 0.0;
    forin(1, size+1)
    {
        minimalMapColumn[i] = getMinElementInColumn(i);
        H += minimalMapColumn[i];
        if(reduce) subtractInColumn(i, minimalMapColumn[i]);
    }
    return H;
}

bool Map::equals(Object &obj)
{
    return Object::equals(obj);
}

void Map::deleteRowAndColumn(int rowNum, int columnNum)
{
    double buffer;
    for (int i = rowNum; i < size + 1; i++)
    {
        for (int j = 0; j < size + 1; j++)
        {
            map[i][j] = map[i + 1][j];
        }
    }
    for (int j = columnNum; j < size + 1; j++)
    {
        for (int i = 0; i < size + 1; i++)
            map[i][j] = map[i][j + 1];
    }
    size--;
    for (int i = 0; i < size + 1; i++)
    {
        for (int j = 0; j < size + 1; j++)
        {
            if (map[0][j] == rowNum && map[i][0] == columnNum)
                map[i][j] = -1;
        }
    }
}

void Map::saveAsReduced()
{
    saveMap(reducedMap);
    reducedSize = size;
}

void Map::saveAsNonReduced()
{
    saveMap(nonreducedMap);
    nonReducedSize = size;
}

void Map::restoreReduced()
{
    restoreMap(reducedMap);
    size = reducedSize;
}

void Map::restoreNonReduced()
{
    restoreMap(nonreducedMap);
    size = nonReducedSize;
}

void Map::doCycle(double& H)
{
    double H0, H1, H2;
    H0 = H;
    H0 += this->getH();
    cout << this->toString();
    cout << "Original H = " << H0 << endl;
    this->nullExchange();
    Point p = this->getExchangeSum();
    cout << p.toString() << " | value = " << this->getNumFromExchangeMap(p.x, p.y) << endl;
    this->setMapValue(p, -1);
    cout << "Set the point to -1 " << endl << this->toString();
    this->clearMinimalMaps();
    this->fillMinimalMaps();
    H1 = H0 + this->getHWithoutReduce();
    cout << "New H without reducing = " << H1 << endl;
    cout << this->toString();
    this->saveAsNonReduced();
    this->deleteRowAndColumn(p.x, p.y);
    H2 = H0 + this->getHWithoutReduce();
    cout << "New H with reducing = " << H2 << endl;
    cout << this->toString();
    this->saveAsReduced();
    if(H1 == H2)
    {
        cout << "H1 = H2. Choose reduced matrix." << endl;
        H0 = H1;
    }
    else if(H1 <= H2)
    {
        cout << "The not reduced matrix has less weight. Choose it!" << endl;
        this->restoreNonReduced();
        H0 = H1;
    }
    else
    {
        cout << "The reduced matrix has less weight. Choose it!" << endl;
        H0 = H2;
    }
    H = H0;
}

void Map::clearExchangeMap()
{
    forin(0, MAX_ELEMENTS)
        forjn(0, MAX_ELEMENTS)
            exchangedMap[i][j] = 0;
}
