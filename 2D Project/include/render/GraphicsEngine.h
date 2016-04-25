#ifndef GRAPHICSENGINE_H_INCLUDED
#define GRAPHICSENGINE_H_INCLUDED

#include "util/ProgramDefines.h"

#include <GL/glew.h>
#include <glm/detail/type_mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <string>
#include <stdio.h>

#include "util/LoadShaders.h"
#include "render/Drawable.h"
#include "render/Background.h"
#include "Listeners.h"

/**
\file GraphicsEngine.h
\brief Header file for GraphicsEngine.cpp

\version   1.1
\date      Written: 1/9/2016  <BR> Revised: 1/9/2016

*/

/**
\class GraphicsEngine

\brief The GraphicsEngine class is an extension of sf::RenderWindow which
handles all of the graphics rendering in the program.

*/

class UI;
class Background;

class GraphicsEngine : public sf::RenderWindow
{
    friend class Background;

private:
    GLenum mode;              ///< Mode, either point, line or fill.
    int sscount;              ///< Screenshot count to be appended to the screenshot filename.
    GLfloat screenBounds[4];  ///< (l, r, b, t) bounds for the screen.
    GLuint useTextureLoc;     ///< Location ID of the texture use flag in the shader.
    GLuint projLoc;           ///< Uniform location of the projection matrix
    Background *bg;           ///< Background render object
    int texIdx;               ///< Index of the next texture to load

    std::vector<Drawable*> objects;
    std::vector<Drawable*> undoStack;
    std::vector<Drawable*> redoStack;

    void screenshot(std::string ext);
    void setProjectionMatrix();

public:
    GraphicsEngine(std::string, GLint, GLint);
    ~GraphicsEngine();

    static GLuint defaultShader;

    void display();
    void changeMode();
    void screenshotPNG();
    void screenshotJPG();
    void undo();
    void redo();
    void resize();
    void setSize(unsigned int, unsigned int);
    void addObject(Drawable* obj, bool removable = true);
    GLuint loadTexture(std::string path);
    void activateTexture(int texId);
    GLfloat* getScreenBounds();
};

#endif // GRAPHICSENGINE_H_INCLUDED
