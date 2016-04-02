#ifndef POLYGON_H_INCLUDED
#define POLYGON_H_INCLUDED

#include <SFML/Graphics.hpp>
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

class Bubble
{
private:
    GLfloat radius;        ///< Radius of the star.
    sf::Vector2f motion;
    lib::Point2D center;       ///< Coordinates of the center of the bubble.
    lib::ColorRGB color;      ///< RGB color of the bubble.

    GLuint PolygonVAO;     ///< Vertex Array Object ID.
    GLuint ArrayBuffer;    ///< Vertex and Color Information Array Buffer ID.
    GLuint PolygonEBO;     ///< Indices Array Object ID.

    GLint vPosition;       ///< Array Buffer position index.
    GLint vColor;          ///< Array Buffer color index.

    void LoadDataToGraphicsCard();

public:
    Bubble(sf::Vector2f m, lib::Point2D c, lib::ColorRGB col, GLfloat r);
    ~Bubble();

    GLfloat getRadius();
    lib::Point2D getCenter();
    sf::Vector2f* getMotion();

    void setCenter(lib::Point2D c);

    void draw();
};

#endif // POLYGON_H_INCLUDED
