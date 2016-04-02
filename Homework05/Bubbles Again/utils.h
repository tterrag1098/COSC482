#ifndef STRUCTS_H_INCLUDED
#define STRUCTS_H_INCLUDED

#include "GL/gl.h"
#include <random>

/**
\file structs.h
\brief Header file with some useful structs for handling rendering data

\author    
\version   1.0
\date      Written: 2/16/2015 <BR> Revised: 2/16/2015
*/

namespace lib
{

/* Points */

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

/* Colors */

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

/** \brief Represents a color in HSV format (hue-saturation-value). */
struct ColorHSV
{
    float h, s, v;
};

/** \brief Converts a color in RGB format into HSV format */
ColorHSV to_hsv(ColorRGB in);

/** \brief Converts a color in HSV format into RGB format */
ColorRGB to_rgb(ColorHSV in);

/* Vertices */

/** \brief Represents a vertex in two dimensions, which consists of a Point2D and a ColorRGB. */
struct Vertex2D
{
    Point2D p;
    ColorRGB c;
};

/* Misc Utils */

/** \return returns a random float value between 0 and 1. Does *not* call srand. */
float rand_float();

}

#endif // STRUCTS_H_INCLUDED
