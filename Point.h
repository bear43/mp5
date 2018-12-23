//
// Created by kostya on 23.12.18.
//

#ifndef UNTITLED_POINT_H
#define UNTITLED_POINT_H

#include <iostream>
#include <cstring>
#include <sstream>
#include "Object.h"

using namespace std;


class Point : public Object
{
public:
    int x;
    int y;
    Point(int x, int y);
    Point();
    string toString() override;
    bool equals(Object& obj) override;
};


#endif //UNTITLED_POINT_H
