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
#include "ProgramDefines.h"
#include "SphericalCamera.h"
#include "YPRCamera.h"
#include "Axes.h"
#include "BeachBall.h"

/**
\file GraphicsEngine.h
\brief Header file for GraphicsEngine.cpp

\author    
\version   1.2
\date      Written: 2/28/2016  <BR> Revised: 2/28/2016

*/

/**
\class GraphicsEngine

\brief The GraphicsEngine class is an extension of sf::RenderWindow which
handles all of the graphics rendering in the program.

*/

class GraphicsEngine : public sf::RenderWindow
{
private:
    GLenum mode;       ///< Mode, either line or fill.
    GLenum frontface;  ///< The front face, CW or CCW
    GLenum cullface;   ///< Face mode for culling.

    int sscount;            ///< Screenshot count to be appended to the screenshot filename.
    Axes coords;            ///< Axes Object

    BeachBall balls[7];     ///< An array of all the beach balls to be drawn.

    GLuint PVMLoc;     ///< Location ID of the PVM matrix in the shader.

    SphericalCamera sphcamera;  ///< Spherical Camera
    YPRCamera yprcamera;        ///< Yaw-Pitch-Roll Camera
    int CameraNumber;           ///< Camera number 1 = spherical, 2 = yaw-pitch-roll.
    int animationCounter = 0;       ///< Count for rotation of balls

    glm::mat4 projection;       ///< Projection Matrix

    GLboolean drawAxes;        ///< Boolean for axes being drawn.
    GLboolean isPrespective;   ///< Boolean for perspective verses orthographic.
    GLboolean culling;         ///< Boolean for culling or not.
    GLboolean drawFaces = true;///< Boolean for drawing faces.
    GLboolean drawBorders;     ///< Boolean for drawing face borders.

    void screenshot(std::string ext);
    void printOpenGLErrors();
    void print_GLM_Matrix(glm::mat4 m);
    void renderBall(BeachBall *ball, glm::mat4 view, glm::vec3 axis, float rot, glm::mat4 pre = glm::mat4(1.0f));

public:
    GraphicsEngine(std::string, GLint, GLint);
    ~GraphicsEngine();

    void display();
    void changeMode();
    void changeCullface();
    void changeFrontFace();
    void changeCulling();
    void screenshotPNG();
    void screenshotJPG();
    void resize();
    void setSize(unsigned int, unsigned int);

    void setDrawManyBoxes(GLboolean b);
    void setDrawBoxes(GLboolean b);
    void setDrawAxes(GLboolean b);
    void setDrawSurface(GLboolean b);

    void changeDrawFaces();
    void changeDrawBorders();

    void setProjectionMatrix();
    void setPrespective(GLboolean b);
    GLboolean getPrespective();
    GLboolean isSphericalCameraOn();
    void setSphericalCameraOn();
    GLboolean isYPRCameraOn();
    void setYPRCameraOn();

    SphericalCamera* getSphericalCamera();
    YPRCamera* getYPRCamera();
};

#endif // GRAPHICSENGINE_H_INCLUDED
