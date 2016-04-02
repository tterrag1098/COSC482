#ifndef STRUCTS_H_INCLUDED
#define STRUCTS_H_INCLUDED

#include "GL/gl.h"

/**
\file structs.h
\brief Header file with some useful structs for handling rendering data

\author    
\version   1.0
\date      Written: 2/16/2015 <BR> Revised: 2/16/2015
*/

namespace lib
{

/** \brief Represents a point in two dimensions. */
struct Point2D
{
    GLfloat x, y;
};

/** \brief Represents a point in three dimensions. */
struct Point3D
{
    GLfloat x, y, z;
};

/** \brief Represents a color. */
struct ColorRGB
{
    GLfloat r, g, b;
};

static const ColorRGB RED = {1.0f, 0.0f, 0.0f};
static const ColorRGB GREEN = {0.0f, 1.0f, 0.0f};
static const ColorRGB BLUE = {0.0f, 0.0f, 1.0f};
static const ColorRGB BLACK = {0.0f, 0.0f, 0.0f};
static const ColorRGB WHITE = {1.0f, 1.0f, 1.0f};

/** \brief Represents a color with alpha. */
struct ColorRGBA
{
    ColorRGB color;
    GLfloat a;
};

/** \brief Represents a vertex in two dimensions, which consists of a Point2D and a ColorRGB. */
struct Vertex2D
{
    Point2D p;
    ColorRGB c;
};

}

#endif // STRUCTS_H_INCLUDED
