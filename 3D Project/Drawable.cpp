#include "Drawable.h"
#include "GraphicsEngine.h"

Drawable::Drawable(Material mat, bool indexed, bool visible) : material(mat), indexed(indexed), visible(visible)
{
    if (visible)
    {
        glGenVertexArrays(1, &vboptr);
        glGenBuffers(1, &bufptr);
        if (indexed)
        {
            glGenBuffers(1, &eboptr);
        }
    }
}

Drawable::~Drawable()
{
    if (visible)
    {
        glBindVertexArray(vboptr);
        glDeleteBuffers(1, &bufptr);
        if (indexed)
        {
            glDeleteBuffers(1, &eboptr);
        }
        glDeleteVertexArrays(1, &vboptr);
    }

    for (Drawable *d : children)
    {
        delete d;
    }
}

void Drawable::load()
{
    verts.clear();
    colors.clear();
    uvs.clear();
    indices.clear();

    refresh();

    if (visible)
    {
        int vPosition = 0;
        int vColor = 1;
        int vTex = 2;

        GLuint vertSize = sizeof(glm::vec3) * verts.size();
        GLuint colorSize = sizeof(glm::vec4) * colors.size();
        GLuint uvSize = sizeof(glm::vec2) * uvs.size();

        glBindVertexArray(vboptr);

        if (indexed)
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboptr);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * indices.size(), &indices[0], GL_DYNAMIC_DRAW);
        }

        glBindBuffer(GL_ARRAY_BUFFER, bufptr);
        glBufferData(GL_ARRAY_BUFFER, vertSize + colorSize + uvSize, NULL, GL_DYNAMIC_DRAW);

        glBufferSubData(GL_ARRAY_BUFFER, 0, vertSize, &verts[0]);
        glBufferSubData(GL_ARRAY_BUFFER, vertSize, colorSize, &colors[0]);
        glBufferSubData(GL_ARRAY_BUFFER, vertSize + colorSize, uvSize, &uvs[0]);

        glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
        glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertSize));
        glVertexAttribPointer(vTex, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertSize + colorSize));

        glEnableVertexAttribArray(vPosition);
        glEnableVertexAttribArray(vColor);
        glEnableVertexAttribArray(vTex);
    }

    for (Drawable *d : children)
    {
        d->load();
    }
}

void Drawable::refresh() {}

void Drawable::draw(GraphicsEngine *ge)
{
    ge->updateModelMat(getModelMat());
    ge->setUseLighting(useLighting);
    ge->setUseTexture(useTexture);

    if (visible)
    {
        glBindVertexArray(vboptr);
        if (indexed)
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboptr);
            glDrawElements(getDrawMode(), indices.size(), GL_UNSIGNED_INT, NULL);
        }
        else
        {
            glDrawArrays(getDrawMode(), 0, verts.size());
        }
    }

    ge->setUseLighting(true);
    ge->setUseTexture(true);

    for (Drawable *d : children)
    {
        d->draw(ge);
    }
}

glm::mat4 Drawable::getModelMat()
{
    return glm::mat4(1.0);
}

Material Drawable::getMaterial()
{
    return material;
}

void Drawable::vert(glm::vec3 pos, glm::vec4 color, glm::vec2 uv)
{
    verts.push_back(pos);
    colors.push_back(color);
    uvs.push_back(uv);
}

void Drawable::index_quad(int count)
{
    for (int i = 0; i < count * 4; i += 4)
    {
        std::vector<int> quad = {i, i + 3, i + 2, i, i + 2, i + 1};
        indices.insert(indices.end(), quad.begin(), quad.end());
    }
}

GLuint Drawable::getDrawMode() const
{
    return GL_TRIANGLES;
}
