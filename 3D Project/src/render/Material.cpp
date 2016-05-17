#include "Material.h"


/**
\file Material.cpp
\brief Implementation of the Material class.

\author    Don Spickler
\version   1.1
\date      Written: 2/28/2016  <BR> Revised: 2/28/2016

*/

/**
\brief Constructor, default.

*/

Material::Material() : Material(0, 0, 0, 0, 0, 0, 0) {}


/**
\brief Sets all of the material attributes.

\param a --- Ambient color of the material.
\param d --- Diffuse color of the material.
\param s --- Specular color of the material.
\param e --- Emission color of the material.
\param sh --- Shininess exponent of the material.

*/

Material::Material(GLuint d, GLuint s, glm::vec4 e, float sh) : diffuse(d), specular(s), emission(e), shininess(sh) {}


/**
\brief Sets all of the material attributes using floats.

\param ar, ag, ab, aa --- Ambient color of the light.
\param dr, dg, db, da --- Diffuse color of the light.
\param sr, sg, sb, sa --- Specular color of the light.
\param er, eg, eb, ea --- Emission color of the light.
\param sh --- Shininess exponent of the material.

*/

Material::Material(GLuint d, GLuint s, float er, float eg, float eb, float ea, float sh) : Material(d, s, {er, eg, eb, ea}, sh) {}


/**
\brief Sets all of the material attributes.

\param a --- Ambient color of the material.
\param d --- Diffuse color of the material.
\param s --- Specular color of the material.
\param e --- Emission color of the material.
\param sh --- Shininess exponent of the material.

*/

void Material::setMaterial(GLuint d, GLuint s, glm::vec4 e, float sh)
{
    diffuse = d;
    specular = s;
    emission = e;
    shininess = sh;
}

/**
\brief Sets all of the material attributes using floats.

\param ar, ag, ab, aa --- Ambient color of the light.
\param dr, dg, db, da --- Diffuse color of the light.
\param sr, sg, sb, sa --- Specular color of the light.
\param er, eg, eb, ea --- Emission color of the light.
\param sh --- Shininess exponent of the material.

*/

void Material::setMaterial(GLuint d, GLuint s, float er, float eg, float eb, float ea, float sh)
{
    Material::setMaterial(d, s, {er, eg, eb, ea}, sh);
}

/**
\brief Destructor

No implementation needed at this point.

*/

Material::~Material(){}

GLuint Material::getDiffuse()
{
    return diffuse;
}

GLuint Material::getSpecular()
{
    return specular;
}

/**
\brief Returns the emission color vector of the material.

*/

glm::vec4 Material::getEmission()
{
    return emission;
}

/**
\brief Returns the shininess exponent of the material.

*/

float Material::getShininess()
{
    return shininess;
}


/**
\brief Sets the emission material color.

\param e --- Emission color of the material.

*/

void Material::setEmission(glm::vec4 e)
{
    emission = e;
}

/**
\brief Sets the shininess exponent of the material.

\param sh --- Shininess exponent.

*/

void Material::setShininess(float sh)
{
    shininess = sh;
}

/**
\brief Sets all of the emission attributes using floats.

\param er, eg, eb, ea --- Emission color of the light.

*/

void Material::setEmission(float er, float eg, float eb, float ea)
{
    emission = glm::vec4(er, eg, eb, ea);
}
