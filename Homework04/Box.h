#ifndef BOX_H_INCLUDED
#define BOX_H_INCLUDED

#include <GL/glew.h>
#include <iostream>

#include "ProgramDefines.h"
#include "utils.h"

/**
\file Box.h

\brief Header file for Box.cpp

\author    Don Spickler
\version   1.2
\date      Written: 1/11/2016  <BR> Revised: 1/12/2016

*/

/**
\class Box

\brief The Box class holds position and color data for a multicolored rectangle.  It also has
facilities for loading the data to the graphics card and invoking draw commands on the data.

*/

using namespace lib;

class Box
{
private:
    GLfloat width;        ///< Width of the box.
    GLfloat height;       ///< Height of the box.
    Point2D center;       ///< The center of the box.
    ColorRGB color;       ///< The color of the box.

    GLuint BoxVAO;        ///< Vertex Array Object ID.
    GLuint ArrayBuffer;   ///< Vertex and Color Information Array Buffer ID.
    GLuint BoxEBO;        ///< Indices Array Object ID.

    GLint vPosition;      ///< Array Buffer position index.
    GLint vColor;         ///< Array Buffer color index.

    bool hover;           ///< Active if this box is being hovered over. Makes it draw red.

    void LoadDataToGraphicsCard();

public:
    Box(Point2D c = {0, 0}, GLfloat w = 1, GLfloat h = 1);
    ~Box();

    bool contains(Point2D p);

    void setWidth(GLfloat w);
    void setHeight(GLfloat h);
    void setCenter(Point2D p);
    void setColor(ColorRGB c);
    void setHover(bool h);

    GLfloat getWidth();
    GLfloat getHeight();
    Point2D getCenter();

    void draw();

    int index;
    static int index_tracker;
};

#endif // BOX_H_INCLUDED
