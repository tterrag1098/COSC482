#ifndef OBJMODEL_H_INCLUDED
#define OBJMODEL_H_INCLUDED

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "ProgramDefines.h"

/**
\file ObjModel.h
\brief Header file for ObjModel.cpp

\author    Don Spickler
\version   1.1
\date      Written: 4/10/2016  <BR> Revised: 4/10/2016

*/

/**
\class ObjModel

\brief Model loader class for simple Wavefront obj files.

Loads in a simple Wavefront obj file, one that contains only vertex, normal, and
texture coordinate data.  No other data is read in and the vertex data most be in
triangulated form.

Code was altered from Tutorial 7 : Model loading from http://www.opengl-tutorial.org/.

*/

class ObjModel
{
private:
    GLuint vboptr;  ///< ID for the VBO.
    GLuint bufptr;  ///< ID for the array buffer.
    GLuint eboptr;  ///< ID for the index array buffer.

    std::vector<glm::vec3> vertices;  ///< Vector for storing the vertex data.
    std::vector<glm::vec2> texcoords; ///< Vector for storing the texture coordinate data.
    std::vector<glm::vec3> normals;   ///< Vector for storing the normal vector data.

    void LoadDataToGraphicsCard();

public:
    ObjModel();
    ~ObjModel();

    bool Load(std::string filename);

    void draw();
};

#endif // OBJMODEL_H_INCLUDED
