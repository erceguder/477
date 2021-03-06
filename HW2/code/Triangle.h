#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__

#include "Vec4.h"
#include "Line.h"
#include <vector>

class Triangle
{
public:
    int vertexIds[3];
    Vec4 vertices[3];
    Line lines[3];
    bool culled;

    Triangle();
    Triangle(int vid1, int vid2, int vid3);
    Triangle(const Triangle &other);

    void setVertices(vector<Vec3*>& vertices);
    void setColours(vector<Color*>& colours);
    void setLines();

    void clip();
    void applyCulling();

    void draw(vector<vector<Color > >&, bool, int, int);
};


#endif
