#ifndef POLYGON_H_INCLUDED
#define POLYGON_H_INCLUDED

#include <GL/glew.h>
#include <iostream>
#include <math.h>

#include "utils.h"
#include "ProgramDefines.h"

/**
\file Polygon.h

\brief Header file for Polygon.cpp

\author    Don Spickler
\version   1.2
\date      Written: 1/11/2016  <BR> Revised: 1/12/2016

*/

/**
\class Polygon

\brief The Polygon class holds position and color data for a single colored polygon.  It
also has facilities for loading the data to the graphics card and invoking draw commands
on the data.

*/

class Star
{
private:
    GLfloat radius;        ///< Radius of the star.
    GLint points;           ///< The number of points of the star.
    lib::Point2D center;       ///< Coordinates of the center of the star.
    lib::ColorRGB *color;      ///< RGB color, of the star. NULL for randomized.

    GLuint PolygonVAO;     ///< Vertex Array Object ID.
    GLuint ArrayBuffer;    ///< Vertex and Color Information Array Buffer ID.
    GLuint PolygonEBO;     ///< Indices Array Object ID.

    GLint vPosition;       ///< Array Buffer position index.
    GLint vColor;          ///< Array Buffer color index.

    void LoadDataToGraphicsCard();

public:
    Star(lib::Point2D c, GLfloat r, GLint p);
    ~Star();

    void setRadius(GLfloat r);
    void setPoints(GLint s);
    void setCenter(lib::Point2D point);
    void setColor(lib::ColorRGB* color);
    void setRandomizedColor();
    GLfloat getRadius();
    GLint getPoints();
    lib::ColorRGB* getColor();
    void getCenter(lib::Point2D* c);

    void draw();
};

#endif // POLYGON_H_INCLUDED
