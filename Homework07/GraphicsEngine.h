#ifndef GRAPHICSENGINE_H_INCLUDED
#define GRAPHICSENGINE_H_INCLUDED

#include <map>

#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <string>
#include <stdio.h>

#define GLM_SWIZZLE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/euler_angles.hpp>

#include "LoadShaders.h"
#include "ProgramDefines.h"
#include "SphericalCamera.h"
#include "YPRCamera.h"
#include "Axes.h"
#include "teapot.h"
#include "Material.h"
#include "Light.h"
#include "MaterialPresets.h"
#include "Models.h"

/**
\file GraphicsEngine.h
\brief Header file for GraphicsEngine.cpp

\author    
\version   1.2
\date      Written: 2/28/2016  <BR> Revised: 4/1/2016

*/

/**
\class GraphicsEngine

\brief The GraphicsEngine class is an extension of sf::RenderWindow which
handles all of the graphics rendering in the program.

*/

class GraphicsEngine : public sf::RenderWindow
{
private:
    GLenum mode;    ///< Mode, either point, line or fill.
    int sscount;    ///< Screenshot count to be appended to the screenshot filename.
    Axes coords;    ///< Axes Object
    Drawable *active; ///< Active object to draw.
    Material mat; ///< Currently active material

    std::map<int, Drawable*> models; ///< Map of all models.
    std::map<int, Material> materials; ///< Map of all materials.

    glm::ivec3 rotation;
    glm::vec3 translation;

    GLuint ModelLoc;   ///< Location ID of the Model matrix in the shader.
    GLuint NormalLoc;  ///< Location ID of the Normal matrix in the shader.
    GLuint PVMLoc;     ///< Location ID of the PVM matrix in the shader.
    GLuint shaderBasic;   ///< ID of the basic shader program.
    GLuint shaderHalfway; ///< ID of the halfway shader program.
    GLuint program; ///< ID of the active shader.

    SphericalCamera sphcamera;  ///< Spherical Camera
    YPRCamera yprcamera;        ///< Yaw-Pitch-Roll Camera
    int CameraNumber;           ///< Camera number 1 = spherical, 2 = yaw-pitch-roll.
    SphericalCamera LtPos;      ///< Spherical "Camera" to control position of the light.

    Light lt;      ///< Light object.

    Models lightobj;  ///< Used for sphere at light source.

    glm::mat4 projection;  ///< Projection Matrix
    glm::mat4 model;       ///< Model Matrix

    GLboolean drawAxes;    ///< Boolean for axes being drawn.

    Models* load(Models *model);
    void loadShaders();
    void updateShader();
    void screenshot(std::string ext);
    void printOpenGLErrors();
    void print_GLM_Matrix(glm::mat4 m);
    void print_GLM_Matrix(glm::mat3 m);

public:
    GraphicsEngine(std::string, GLint, GLint);
    ~GraphicsEngine();

    void display();
    void changeMode();
    void screenshotPNG();
    void screenshotJPG();
    void resize();
    void setSize(unsigned int, unsigned int);
    GLfloat* getScreenBounds();
    void setDrawAxes(GLboolean b);

    GLboolean isSphericalCameraOn();
    void setSphericalCameraOn();
    GLboolean isYPRCameraOn();
    void setYPRCameraOn();

    void loadLight(Light Lt);
    void loadMaterial(Material Mat);

    void turnLightOn();
    void turnLightOff();

    void rotate(glm::ivec3 vec);
    void translate(glm::vec3 vec);

    void activateModel(int c);
    void activateMaterial(int c);

    void useBasicShader();
    void useHalfwayShader();

    SphericalCamera* getLtPos();
    SphericalCamera* getSphericalCamera();
    YPRCamera* getYPRCamera();
};

#endif // GRAPHICSENGINE_H_INCLUDED
