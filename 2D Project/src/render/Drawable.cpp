#include "render/Drawable.h"

Drawable::Drawable(bool indexed) : indexed(indexed)
{
    glGenVertexArrays(1, &vboptr);
    glGenBuffers(1, &bufptr);
    if (indexed)
    {
        glGenBuffers(1, &eboptr);
    }
}

Drawable::~Drawable()
{
    glBindVertexArray(vboptr);
    glDeleteBuffers(1, &bufptr);
    if (indexed)
    {
        glDeleteBuffers(1, &eboptr);
    }
    glDeleteVertexArrays(1, &vboptr);
}

void Drawable::load()
{
    verts.clear();
    colors.clear();
    indices.clear();

    refresh();

    int vPosition = 0;
    int vColor = 1;

    GLuint vertSize = sizeof(glm::vec2) * verts.size();
    GLuint colorSize = sizeof(glm::vec3) * colors.size();

    glBindVertexArray(vboptr);

    if (indexed)
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboptr);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * indices.size(), &indices[0], GL_DYNAMIC_DRAW);
    }

    glBindBuffer(GL_ARRAY_BUFFER, bufptr);
    glBufferData(GL_ARRAY_BUFFER, vertSize + colorSize, NULL, GL_DYNAMIC_DRAW);

    glBufferSubData(GL_ARRAY_BUFFER, 0, vertSize, &verts[0]);
    glBufferSubData(GL_ARRAY_BUFFER, vertSize, colorSize, &colors[0]);

    glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glVertexAttribPointer(vColor, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertSize));

    glEnableVertexAttribArray(vPosition);
    glEnableVertexAttribArray(vColor);
}

void Drawable::draw()
{
    glBindVertexArray(vboptr);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboptr);
    glDrawElements(getDrawMode(), indexed ? indices.size() : verts.size(), GL_UNSIGNED_INT, NULL);
}

GLuint Drawable::getDrawMode()
{
    return GL_TRIANGLES;
}
