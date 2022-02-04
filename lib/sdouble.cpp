#include "sdouble.h"
using namespace std;

double sdouble::setval(int decimal, float fraction) {
    decimal_t = decimal;
    this->fraction = fraction;
    v = decimal + fraction;
    return v;
}

double sdouble::setval(int decimal) {
    decimal_t = decimal;
    this->fraction = 0;
    v = decimal;
    return v;
}

double sdouble::setval(float fraction) {
    decimal_t = 0;
    this->fraction = fraction;
    v = fraction;
    return v;
}