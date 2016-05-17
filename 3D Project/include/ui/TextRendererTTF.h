#ifndef TEXTRENDERERTTF_H_INCLUDED
#define TEXTRENDERERTTF_H_INCLUDED

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include <SFML/System/Vector2.hpp>

#include "Shader.h"

#include <ft2build.h>
#include FT_FREETYPE_H

/**
\file TextRendererTTF.h

\brief Header file for TextRendererTTF.cpp

The majority of the code in this class structure was taken from
OpenGL Programming wikibook: http://en.wikibooks.org/wiki/OpenGL_Programming
The original file was in the public domain and was written by Guus Sliepen and
Sylvain Beucler.  It was then altered by Don Spickler to remove its dependency
on SDL and make it more transferable between windowing systems. In addition,
the code was written to be easy to integrate into the modern OpenGL graphics
rendering system and rotation of text was added to the functionality.

There are several dependencies needed to use this class,

- Freetype libraries
- glm matrix arithmetic headers
- LoadShaders.h and LoadShaders.cpp to be compiled into the project.
- GLEW

\author    Guus Sliepen, Sylvain Beucler, Don Spickler, and Garrett Spicer-Davis
\version   1.2
\date      Written: 1/15/2016  <BR> Revised: 5/16/2016

*/

/**
\class TextRendererTTFPoint Struct

\brief Coordinate and texture coordinate positions needed for the font rendering shader.

*/

struct TextRendererTTFPoint
{
    GLfloat x;
    GLfloat y;
    GLfloat s;
    GLfloat t;
};


/**
\class TextRendererTTF

\brief This class encapsulates the details of rendering a TrueType font on an OpenGL
window.

This class encapsulates the details of rendering a TrueType font on an OpenGL
window as a 2-D overlay.  There are accessor methods for changing the font size and color.
Methods for loading a TrueType font file, finding the pixel width of a string with the
current font and size, and a draw command allowing for placement and rotation.

\note The current window width and height need to be loaded into the structure for the
position and font size to correspond to a number of pixels.

\note To set the size, simply call the setScreenSize(w, h) method where w and h are the width
and height, in pixels, of the OpenGL window.  This can be done in the resize routine of
the windowing system or simply in the display routine before the text is rendered.

\note The draw method has the form, draw(text, xpos, ypos, rot) where text is either a char*
type string or a std::string type. The parameters xpos and ypos are the x and y positions
of the lower left corner of the containing box for the text given in pixels if the window
width and height were set correctly.  The rot parameter is optional, its default is 0,
and it specifies the counter clockwise rotation of the text in degrees centered around
the (xpos, ypos) point.

\note In this system, positions are given in terms of pixel locations with the (0, 0) location
being in the lower left corner of the OpenGL screen.

*/

class TextRendererTTF
{
private:
    GLuint ScreenWidth;
    GLuint ScreenHeight;
    GLfloat color[4];         ///< Text Color in (r, g, b, a)
    GLuint TextVBO;           ///< Vertex Buffer Object ID.
    GLuint TextVAO;           ///< Vertex Array Object ID.
    GLuint fontSize;          ///< Font size in pixels.

    GLboolean fontLoadError;  ///< Font loading error flag.
    GLboolean shaderError;    ///< Shader loading error flag.
    GLboolean freetypeError;  ///< Freetype loading error flag.
    GLboolean glewError;      ///< GLEW loading error flag.

    Shader shader;           ///< Text rendering shader program.
    GLint attribute_coord;    ///< Coordinate attribute location for shader program.
    GLint uniform_tex;        ///< Texture attribute location for shader program.
    GLint uniform_color;      ///< Color attribute location for shader program.
    GLint rotmat;             ///< Scale, rotate and translate matrix location for shader program.

    FT_Library ft;            ///< Freetype Library variable.
    FT_Face face;             ///< Freetype font face variable.

public:
    TextRendererTTF(std::string fontFile = "");
    ~TextRendererTTF();

    void setScreenSize(GLuint w, GLuint h);
    void setScreenSize(sf::Vector2u size);

    void setColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
    void setColor(GLfloat c[4]);
    void setColor(glm::vec4 col);
    void setFontSize(GLuint sz);
    GLuint getFontSize() const;
    void loadFont(std::string fontFile);
    GLboolean isError() const;

    int textWidth(std::string text) const;
    int textWidth(const char* text, int n) const;

    void draw(std::string text, GLuint xpos, GLuint ypos, GLfloat rot = 0) const;
    void draw(const char* text, GLuint xpos, GLuint ypos, GLfloat rot = 0) const;
};

#endif // TEXTRENDERERTTF_H_INCLUDED
