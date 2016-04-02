#ifndef SIMPLESURFACE_H_INCLUDED
#define SIMPLESURFACE_H_INCLUDED

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "ProgramDefines.h"
#include "utils.h"

/**
\file BeachBall.h

\brief Header file for BeachBall.cpp

\author    
\version   1.2
\date      Written: 2/28/2016  <BR> Revised: 3/28/2016

*/

/**
\class BeachBall

\brief The BeachBall class draws a sphere colored like a beach ball.

*/

class BeachBall
{
private:
    glm::vec3 pos;  ///< Position of the beach ball
    GLfloat radius; ///< Radius of the beach ball

    int numElements; ///< Number of elements to draw.

    GLuint vboptr;  ///< ID for faces VBO.
    GLuint eboptr;  ///< ID for faces index array.
    GLuint bufptr;  ///< ID for faces array buffer.

    GLuint vboptrborder;  ///< ID for faces VBO.
    GLuint eboptrborder;  ///< ID for faces index array.
    GLuint bufptrborder;  ///< ID for faces array buffer.

    GLboolean drawFaces;      ///< Boolean to draw the faces.
    GLboolean drawBorder;     ///< Boolean to draw the border.

    void LoadDataToGraphicsCard();

public:
    BeachBall();
    ~BeachBall();

    void setDrawBorder(GLboolean d);
    void setDrawFaces(GLboolean d);

    glm::vec3 getPos();

    BeachBall* setPos(glm::vec3 pos);
    BeachBall* setRadius(GLfloat radius);

    GLboolean getDrawBorder();
    GLboolean getDrawFaces();
    GLboolean getColorByHeight();

    void setBorderColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a = 1);

    void draw();
};

#endif // SIMPLESURFACE_H_INCLUDED
