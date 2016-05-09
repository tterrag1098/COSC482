#ifndef GRAPHICSENGINE_H_INCLUDED
#define GRAPHICSENGINE_H_INCLUDED

#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <stdio.h>

#define GLM_SWIZZLE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "ProgramDefines.h"
#include "SphericalCamera.h"
#include "YPRCamera.h"
#include "Axes.h"
#include "Material.h"
#include "Light.h"
#include "MaterialPresets.h"
#include "Models.h"
#include "ObjModel.h"
#include "PhysicsEngine.h"
#include "BodyModel.h"

/**
\file GraphicsEngine.h
\brief Header file for GraphicsEngine.cpp

\author    Don Spickler
\version   1.2
\date      Written: 4/5/2016  <BR> Revised: 4/6/2016

*/

/**
\class GraphicsEngine

\brief The GraphicsEngine class is an extension of sf::RenderWindow which
handles all of the graphics rendering in the program.

*/

class Drawable;

class GraphicsEngine : public sf::RenderWindow
{
private:
    GLenum mode;    ///< Mode, either point, line or fill.
    int sscount;    ///< Screenshot count to be appended to the screenshot filename.

    std::vector<BodyDrawable*> objects;

    SphericalCamera sphcamera;   ///< Spherical Camera
    YPRCamera yprcamera;         ///< Yaw-Pitch-Roll Camera
    int CameraNumber;            ///< Camera number 1 = spherical, 2 = yaw-pitch-roll.
    GLuint nextLight = 0;

    Material mat;         ///< Material of the current object.
    GLuint texID[6];      ///< Texture IDs.
    GLuint CubeMapTexId;  ///< Cube Map Texture ID.

    Models CMSphere;  ///< Sphere Object for Cube Map

    glm::mat4 projection;  ///< Projection Matrix
    glm::mat4 view;        ///< View Matrix
    glm::mat4 model;       ///< Model Matrix
    glm::mat4 textrans;    ///< Texture transformation matrix.

    GLuint worldFbo;
    GLuint screenVao;
    GLuint fboTex;
    GLuint rbo;

    PhysicsEngine *pe;

    void screenshot(std::string ext);
    void printOpenGLErrors();
    void print_GLM_Matrix(glm::mat4 m);
    void print_GLM_Matrix(glm::mat3 m);

public:
    GraphicsEngine(std::string, GLint, GLint);
    ~GraphicsEngine();

    static GLuint ModelLoc;       ///< Location ID of the Model matrix in the shader.
    static GLuint NormalLoc;      ///< Location ID of the Normal matrix in the shader.
    static GLuint PVMLoc;         ///< Location ID of the PVM matrix in the shader.
    static GLuint texTransLoc;    ///< Location ID of the texture transformation matrix in the shader.

    Shader fboShader;      ///< ID of the shader program.
    Shader screenShader;   ///< ID of the post-processing shader.
    Shader cmShader;       ///< ID of the cube map shader program.

    void display();
    void changeMode();
    void screenshotPNG();
    void screenshotJPG();
    void resize();
    void setSize(unsigned int, unsigned int);
    void addObject(BodyDrawable* obj, bool removable = true);
    GLfloat* getScreenBounds();

    void updateModelMat(glm::mat4 modelMat);
    void setUseLighting(bool use);
    void setUseTexture(bool use);

    GLboolean isSphericalCameraOn();
    void setSphericalCameraOn();
    GLboolean isYPRCameraOn();
    void setYPRCameraOn();

    void loadLight(Light Lt);
    void loadMaterial(Material Mat);

    void turnLightOn();
    void turnLightOff();
    void turnLightOn(std::string name, int i);
    void turnLightOff(std::string name, int i);
    void turnLightsOn(std::string name, int num);
    void turnLightsOff(std::string name, int num);

    void LoadLights(Light Lt[], std::string name, int num);
    void LoadLight(Light Lt, std::string name, int i);

    SphericalCamera* getLtPos();
    SphericalCamera* getSphericalCamera();
    YPRCamera* getYPRCamera();
};

#endif // GRAPHICSENGINE_H_INCLUDED
