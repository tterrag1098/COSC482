#ifndef STRUCTS_H_INCLUDED
#define STRUCTS_H_INCLUDED

#include "GL/gl.h"

namespace lib
{

struct Point2D
{
    GLfloat x, y;
};

struct Point3D
{
    GLfloat x, y, z;
};

struct ColorRGB
{
    GLfloat r, g, b;
};

struct ColorRGBA
{
    ColorRGB color;
    GLfloat a;
};

struct Vertex2D
{
    Point2D p;
    ColorRGB c;
};

}

#endif // STRUCTS_H_INCLUDED
