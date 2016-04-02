#ifndef GRAPHICSENGINE_H_INCLUDED
#define GRAPHICSENGINE_H_INCLUDED

#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>

#include "LoadShaders.h"
#include "Box.h"
#include "ProgramDefines.h"

/**
\file GraphicsEngine.h
\brief Header file for GraphicsEngine.cpp

\author    Don Spickler
\version   1.1
\date      Written: 1/9/2016  <BR> Revised: 1/9/2016

*/

/**
\class GraphicsEngine

\brief The GraphicsEngine class is an extension of sf::RenderWindow which
handles all of the graphics rendering in the program.

*/

class GraphicsEngine : public sf::RenderWindow
{
private:
    GLenum mode;              ///< Mode, either point, line or fill.
    int sscount;              ///< Screenshot count to be appended to the screenshot filename.
    std::vector<Box*> boxes;   ///< All boxes to draw.
    GLfloat screenBounds[4];  ///< (l, r, b, t) bounds for the screen.

    void screenshot(std::string ext);

public:
    GraphicsEngine(std::string, GLint, GLint);
    ~GraphicsEngine();

    void addBox(Box *box);
    void removeBox(Box *box);
    void clear();

    template <typename Func>
    void forEachBox(Func f)
    {
        for (Box* b : boxes)
        {
            f(b);
        }
    }

    void display();
    void refresh();
    void changeMode();
    void screenshotPNG();
    void screenshotJPG();
    void resize();
    void setSize(unsigned int, unsigned int);
    GLfloat* getScreenBounds();
};

#endif // GRAPHICSENGINE_H_INCLUDED
