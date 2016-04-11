#ifndef BOX_H_INCLUDED
#define BOX_H_INCLUDED

#include <GL/glew.h>
#include <iostream>
#include <glm/detail/type_vec2.hpp>
#include <glm/detail/type_vec4.hpp>

#include "render/Drawable.h"
#include "util/ProgramDefines.h"
#include "util/utils.h"

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

class Box : public Drawable
{
protected:
    GLfloat width;        ///< Width of the box.
    GLfloat height;       ///< Height of the box.
    glm::vec2 corner;     ///< The corner of the box.
    glm::vec4 color;      ///< The color of the box.

    virtual void refresh() override;

public:
    Box(glm::vec2 c = {0, 0}, GLfloat w = 1, GLfloat h = 1, glm::vec4 col = WHITE);
    ~Box();

    bool contains(glm::vec2 p);

    void setWidth(GLfloat w);
    void setHeight(GLfloat h);
    void setCorner(glm::vec2 c);
    void setColor(glm::vec4 c);
    void setHover(bool h);

    GLfloat getWidth();
    GLfloat getHeight();
    glm::vec2 getCorner();
};

#endif // BOX_H_INCLUDED
