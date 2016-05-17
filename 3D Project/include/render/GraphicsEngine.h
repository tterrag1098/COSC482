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
#include "Material.h"
#include "Light.h"
#include "Models.h"
#include "ObjModel.h"
#include "PhysicsEngine.h"
#include "BodySphere.h"

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
class GhostPlanet;

class GraphicsEngine : public sf::RenderWindow
{
private:
    GLenum mode;    ///< Mode, either point, line or fill.
    int sscount;    ///< Screenshot count to be appended to the screenshot filename.

    std::vector<BodyDrawable*> bodies;
    std::vector<Drawable*> objects;
    std::vector<Drawable*> ui;

    GhostPlanet *ghost;

    BodyDrawable *selected = NULL; ///< Selected object.

    SphericalCamera sphcamera;   ///< Spherical Camera
    YPRCamera yprcamera;         ///< Yaw-Pitch-Roll Camera
    int CameraNumber;            ///< Camera number 1 = spherical, 2 = yaw-pitch-roll.
    GLuint nextLight = 0;
    GLuint useTextureLoc;        ///< Location ID of the texture use flag in the shader.
    int texIdx;                  ///< Index of the next texture to load

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
    GLuint fboTex[2];
    GLuint rbo;
    GLuint pingpongFBO[2];
    GLuint pingpongBuffer[2];

    GLint tempHolder; ///< Temporary holder value for glGet calls.

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
    Shader uiShader;       ///< ID of the ui passthrough shader.
    Shader blurShader;     ///< ID of the gaussian blur shader.

    GLuint uiProjLoc;      ///< Location ID of the UI projection matrix uniform.

    void display();
    void changeMode();
    void screenshotPNG();
    void screenshotJPG();
    void resize();
    void setSize(unsigned int, unsigned int);

    void addBody(BodyDrawable* obj); ///< Adds a physics object to the world. Will be processed for lighting etc.
    void removeBody(const BodyDrawable* obj); ///< Removes a physics object from the world.

    void addObject(Drawable* obj); ///< Adds a non-physics element to the world.
    void addUIElement(Drawable* obj); ///< Adds a static UI element to the screen. Will not be affected by camera movements or post processing.

    void setSelected(BodyDrawable *obj); ///< Force sets the selected object.

    GLuint loadTexture(std::string path, Shader activeShader);
    GLuint loadMaterial(std::string path);

    void activateTexture(int texId, Shader activeShader);
    GLfloat* getScreenBounds();
    BodyDrawable* getSelectedBody() const;
    std::vector<BodyDrawable*> getBodies() const;
    PhysicsEngine* getPhysics() const;

    GhostPlanet* getGhost() const;

    void updateModelMat(glm::mat4 modelMat);
    void setUseLighting(bool use);
    void setFullbright(bool fb);

    GLboolean isSphericalCameraOn();
    void setSphericalCameraOn();
    GLboolean isYPRCameraOn();
    void setYPRCameraOn();

    void loadLight(Light Lt);
    void loadMaterial(Material Mat);

    void rayCastSelect(float mx, float my);

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
