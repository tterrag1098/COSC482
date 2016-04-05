#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "util/ProgramDefines.h"

#include <GL/glew.h>

#include <glm/detail/type_vec2.hpp>
#include <glm/detail/type_vec3.hpp>

#include <vector>

class Drawable
{
public:
    ~Drawable();

    virtual void draw();

protected:
    Drawable(bool indexed);

    void load();

    virtual void refresh(){}

    virtual GLuint getDrawMode();

    std::vector<glm::vec2> verts;
    std::vector<glm::vec3> colors;
    std::vector<GLuint> indices;

private:
    GLuint vboptr;  ///< ID for the VBO.
    GLuint bufptr;  ///< ID for the array buffer.
    GLuint eboptr;  ///< ID for the index array buffer.

    bool indexed;
};

#endif // DRAWABLE_H
