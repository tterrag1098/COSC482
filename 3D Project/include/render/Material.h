#ifndef MATERIAL_H_INCLUDED
#define MATERIAL_H_INCLUDED

#define GLM_SWIZZLE
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

/**
\file Material.h
\brief Header file for Material.cpp

\author    Don Spickler & Garrett Spicer-Davis
\version   1.2
\date      Written: 2/28/2016  <BR> Revised: 2/28/2016

*/

/**
\class Material

\brief The Material class is simply a class for holding Phong model material properties.

This version of Material uses textures for diffuse and specular, rather than a flat color.

*/

class Material
{
private:
    GLuint diffuse, specular; ///< Texture IDs.
    glm::vec4 emission;  ///< Emission color of the material.
    float shininess;     ///< Shininess exponent of the material.

public:
    Material();
    Material(GLuint diffuse, GLuint specular, glm::vec4 e, float sh);

    Material(GLuint diffuse, GLuint specular, float er, float eg, float eb, float ea, float sh);

    ~Material();

    void setMaterial(GLuint diffuse, GLuint specular, glm::vec4 e, float sh);

    void setMaterial(GLuint diffuse, GLuint specular, float er, float eg, float eb, float ea, float sh);

    GLuint getDiffuse();
    GLuint getSpecular();

    glm::vec4 getEmission();
    float getShininess();

    void setDiffuse(GLuint texID);
    void setSpecular(GLuint texID);

    void setEmission(glm::vec4 e);
    void setShininess(float sh);

    void setEmission(float er, float eg, float eb, float ea);

};

#endif // MATERIAL_H_INCLUDED
