#ifndef __Models_h_
#define __Models_h_

#include <GL/glew.h>
#include <math.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <glm/glm.hpp>

#include "ProgramDefines.h"
#include "Drawable.h"

/**
\file Models.h
\brief Header file for Models.cpp

\author    Don Spickler & Garrett Spicer-Davis
\version   1.2
\date      Written: 2/28/2016  <BR> Revised: 5/16/2016

*/

/**
\class Models

\brief The Models class is simply a class for easy construction of a few 3-D
mathematical objects.

Use of this class is straight forward.  Declare a Models object, call one of the create
methods to generate the data sets, call the load method to load the data to the graphics
card (the three parameters are the data positions of the vertices, colors, and normals in
that order, which are expected by the shader), and then in your display function call the
draw method.

~~~~~~~~~~~~~~~{.c}
Models obj;

obj.createSphereOBJ(0.25, 7, 7);
obj.load(0, 1, 2);

obj.draw();
~~~~~~~~~~~~~~~


*/

class Models : public Drawable
{
private:
    GLint lon;         ///< Number of longitudinal divisions.
    GLint lat;         ///< Number of latitude divisions.
    GLfloat *dat;      ///< Pointer to the vertex data.
    GLfloat *normals;  ///< Pointer to the normal data.

    GLint vPosition;   ///< Shader position of the vertex data.
    GLint vColor;      ///< Shader position of the vertex color.
    GLint vNormal;     ///< Shader position of the vertex normal.
    GLint vTex;        ///< Shader position of the texture coordinate.

    GLboolean reload;      ///< Flag to reload the data to the graphics card.
    GLboolean drawFaces;   ///< Flag to draw the faces of the object.

    GLfloat red;    ///< Red component of the object color.
    GLfloat green;  ///< Green component of the object color.
    GLfloat blue;   ///< Blue component of the object color.
    GLfloat alpha;  ///< Alpha component of the object color.

    GLuint vboptr;  ///< ID for the VBO.
    GLuint bufptr;  ///< ID for the data buffer.
    GLuint eboptr;  ///< ID for the index buffer.

    void CrossProd(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2, GLfloat *cx, GLfloat *cy, GLfloat *cz);
    void resetArraySize(GLint ilon, GLint ilat);
    int pos(int i, int j, int k);

public:
    Models(Material mat);
    Models();
    ~Models();

    void load(GLint v, GLint c, GLint n, GLint t);
    void load() override;
    void draw(GraphicsEngine *ge) override;

    void setDrawFaces(GLboolean d);
    void setColorCube(GLboolean d);

    void setColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a);

    void createNormals();
    void reverseNormals();
    void createSphereOBJ(GLfloat r, GLint ilon, GLint ilat);
    void createPartialSphereOBJ(GLfloat r, GLint ilon, GLint ilat, GLfloat begintheta, GLfloat endtheta, GLfloat beginpsy, GLfloat endpsy);
    void createTorusOBJ(GLfloat irad, GLfloat orad, GLint ilon, GLint ilat);
    void createPartialTorusOBJ(GLfloat irad, GLfloat orad, GLint ilon, GLint ilat, GLfloat begintheta, GLfloat endtheta, GLfloat beginpsy, GLfloat endpsy);
    void createTrefoilOBJ(GLfloat amp, GLfloat numtwists, GLfloat rmaj, GLfloat rmin, GLfloat elongfact, GLint lon, GLint lat);
    void createUmbilicTorusOBJ(GLint ilon, GLint ilat);
    void createBraidedTorusOBJ(GLfloat amp, GLfloat numtwists, GLfloat rmaj, GLfloat rmin, GLfloat elongfact, GLint ilon, GLint ilat);
    void createExpHornOBJ(GLfloat r1, GLfloat r2, GLfloat len, GLint ilon, GLint ilat);
    void createQuadHornOBJ(GLfloat r1, GLfloat r2, GLfloat len, GLint ilon, GLint ilat);
    void createHelicalTorusOBJ(GLfloat irad, GLfloat orad, GLfloat strFact, GLfloat begang, GLfloat endang, GLint ilon, GLint ilat);
    void createMobiusOBJ(GLfloat begv, GLfloat endv, GLint ilon, GLint ilat);
    void createTessellatedWallOBJ(GLfloat width, GLfloat height, GLint ilon, GLint ilat);

    void perturbVeritces(float a);
    void perturbNormalsRandom(float a);
};

#endif
