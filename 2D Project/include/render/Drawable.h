#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "util/ProgramDefines.h"

#include <GL/glew.h>

#include <glm/detail/type_vec2.hpp>
#include <glm/detail/type_vec4.hpp>

#include <vector>

class Drawable
{
public:
    ~Drawable();

    virtual void draw() const;
    virtual void resized(int bounds[4]) {}

    virtual Drawable* setSortIndex(int idx);
    virtual int sortIndex() const;

    void load();

protected:
    Drawable(bool indexed = true, bool visible = true);

    void vert(glm::vec2 pos, glm::vec4 color, glm::vec2 uv = {0, 0});
    void index_quad(int count);

    virtual void refresh() {}

    virtual GLuint getDrawMode() const;

    std::vector<glm::vec2> verts;
    std::vector<glm::vec4> colors;
    std::vector<glm::vec2> uvs;
    std::vector<GLuint> indices;

    std::vector<Drawable*> children;

private:
    GLuint vboptr;  ///< ID for the VBO.
    GLuint bufptr;  ///< ID for the array buffer.
    GLuint eboptr;  ///< ID for the index array buffer.

    bool indexed, visible;
    int idx = 0;
};

#endif // DRAWABLE_H
