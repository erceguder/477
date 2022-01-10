#ifndef __LINE_H__
#define __LINE_H__

#include <iostream>

#include "Vec4.h"

using namespace std;


class Line{
public:
    Vec4 v0, v1;
    bool rejected;

    Line(Vec4 v0, Vec4 v1);

    bool visible(double den, double num, double &t_e, double &t_l);
    void clip(double x_min=-1, double x_max=1, double y_min=-1, double y_max=1, double z_min=-1, double z_max=1);

    friend ostream &operator<<(ostream &os, const Line &m);
};


#endif
