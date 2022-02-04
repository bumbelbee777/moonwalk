#include <iostream>
using namespace std;
#ifndef SDOUBLE_H
#define SDOUBLE_H

struct sdouble {
    int decimal_t;
    float fraction;
    double v;
    double setval(int decimal, float fraction);
    double setval(int decimal);
    double setval(float fraction);
};


#endif