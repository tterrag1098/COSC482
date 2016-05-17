#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "ProgramDefines.h"
#include "Material.h"
#include "utils.h"

#include <GL/glew.h>

#include <SFML/System/Vector2.hpp>

#include <glm/glm.hpp>

#include <vector>

class GraphicsEngine;

static const Material white(0, 0, 0, 0, 0, 0, 0);

class Drawable
{
public:
    virtual ~Drawable();

    virtual void draw(GraphicsEngine *ge);

    virtual void load();

    Material getMaterial() const;
    void setMaterial(Material m);

    void setVisible(bool vis);
    bool isVisible() { return visible; }

protected:
    Drawable(Material mat = white, bool indexed = true, bool visible = true);
    Drawable(bool indexed);

    void vert(glm::vec3 pos, glm::vec4 color = WHITE, glm::vec2 uv = {0, 0});
    void vert(glm::vec2 uipos, glm::vec4 color = WHITE, glm::vec2 uv = {0, 0});

    bool visible;

    void index_quad(int count);

    bool useLighting = true;
    bool fullbright = false;

    virtual void refresh();

    virtual GLuint getDrawMode() const;

    virtual glm::mat4 getModelMat() const;

    std::vector<glm::vec3> verts;
    std::vector<glm::vec4> colors;
    std::vector<glm::vec2> uvs;
    std::vector<GLuint> indices;

    std::vector<Drawable*> children;

private:
    GLuint vboptr;  ///< ID for the VBO.
    GLuint bufptr;  ///< ID for the array buffer.
    GLuint eboptr;  ///< ID for the index array buffer.

    bool indexed;
    Material material;

    int quadcount = 0;
};

#endif // DRAWABLE_H
