#ifndef __MESH_H__
#define __MESH_H__

#include <vector>
#include <iostream>
#include <iomanip>

#include "Triangle.h"

using namespace std;

class Mesh
{

public:
    int meshId;
    int type; // 0 for wireframe, 1 for solid
    int numberOfTransformations;
    vector<int> transformationIds;
    vector<char> transformationTypes;
    int numberOfTriangles;
    vector<Triangle> triangles;

    Mesh();
    Mesh(int meshId, int type, int numberOfTransformations,
          vector<int> transformationIds,
          vector<char> transformationTypes,
          int numberOfTriangles,
          vector<Triangle> triangles);

    friend ostream &operator<<(ostream &os, const Mesh &m);
};

#endif
