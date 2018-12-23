//
// Created by kostya on 23.12.18.
//

#include "Point.h"

Point::Point(int x, int y)
{
    this->x = x;
    this->y = y;
}

Point::Point() : Point(0, 0)
{
}

string Point::toString()
{
    stringstream ss;
    ss << "Point: (" << x << ", " << y << ")";
    return ss.str();
}

bool Point::equals(Object &obj)
{
    return x == ((Point&)obj).x && y == ((Point&)obj).y;
}
