//
// Created by kostya on 23.12.18.
//

#ifndef UNTITLED_OBJECT_H
#define UNTITLED_OBJECT_H

#include <iostream>
#include <cstring>
#include <sstream>

using namespace std;

class Object
{
public:
    virtual string toString()
    {
        stringstream ss;
        ss << "Object @" << this;
        return ss.str();
    }
    virtual bool equals(Object& obj)
    {
        return this == &obj;
    }
};


#endif //UNTITLED_OBJECT_H
