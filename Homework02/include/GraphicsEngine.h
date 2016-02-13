#ifndef GRAPHICSENGINE_H_INCLUDED
#define GRAPHICSENGINE_H_INCLUDED

#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <string>
#include <stdio.h>

#include "LoadShaders.h"
#include "Drawable.h"

#define BUFFER_OFFSET(x) ((const void*) (x))

using namespace std;

/**
\file GraphicsEngine.h
\brief Header file for GraphicsEngine.cpp

\author    Don Spickler
\version   1.1
\date      Written: 11/21/2015  <BR> Revised: 11/21/2015

*/

/**
\class GraphicsEngine

\brief The GraphicsEngine class is an extension of sf::RenderWindow which
handles all of the graphics rendering in the program.

*/

class GraphicsEngine : public sf::RenderWindow
{
private:
// Program Data
    std::vector<lib::Drawable*> todraw; ///< Objects to draw on screen
    GLuint Triangles;                   ///< ID of the Triangles VAO
    GLint NumVAOs;                      ///< Number of Vertex Array Objects.
    GLint ArrayBuffer;                  ///< Current position of array buffer data.
    GLint NumBuffers;                   ///< Number of Buffers
    GLuint NumVertices;                 ///< Number of Vertices
    GLenum mode;                        ///< Mode, either line or fill.
    int sscount;                        ///< Screenshot count to be appended to the screenshot filename.

// Position indexes for shader streams
    GLint vPosition;    ///< Vertex data position, for the shader.
    GLint vColor;       ///< Color data position, for the shader.

// Arrays to hold buffer "addresses"
    GLuint *VAOs;       ///< Array of Vertex Array Object addresses.
    GLuint *Buffers;    ///< Array of Buffer addresses.

public:
    GraphicsEngine(string);
    ~GraphicsEngine();

    void init();
    void display();
    void changeMode();
    void screenshot();
    void resize();
    void setSize(unsigned int, unsigned int);
    void add(lib::Drawable*);
};

#endif // GRAPHICSENGINE_H_INCLUDED
