#ifndef GRAPHICSENGINE_H_INCLUDED
#define GRAPHICSENGINE_H_INCLUDED

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <string>
#include <stdio.h>

#include "LoadShaders.h"
#include "Bubble.h"
#include "ProgramDefines.h"

/**
\file GraphicsEngine.h
\brief Header file for GraphicsEngine.cpp

\author    Don Spickler, 
\version   1.2
\date      Written: 1/9/2016  <BR> Revised: 3/4/2016

*/

/**
\class GraphicsEngine

\brief The GraphicsEngine class is an extension of sf::RenderWindow which
handles all of the graphics rendering in the program.

*/

class GraphicsEngine : public sf::RenderWindow
{
private:
    GLenum mode;     ///< Mode, either point, line or fill.
    GLuint program;  ///< Shader program.
    GLuint projLoc;  ///< Location of the projection matrix field in the shader.
    sf::Clock clock; ///< Clock to keep track of movement ticks.
    int sscount;     ///< Screenshot count to be appended to the screenshot filename.
    std::vector<Bubble*> bubbles;       ///< All bubbles to draw.
    GLfloat screenBounds[4];  ///< (l, r, b, t) bounds for the screen.

    void setProjectionMatrix();

public:
    GraphicsEngine(std::string, GLint, GLint);
    ~GraphicsEngine();

    void refresh();
    void display();
    void screenshot(std::string ext);
    void resize();
    void setSize(unsigned int, unsigned int);
    GLfloat* getScreenBounds();
};

#endif // GRAPHICSENGINE_H_INCLUDED
