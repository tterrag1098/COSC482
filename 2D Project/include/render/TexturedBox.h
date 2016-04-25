#ifndef TEXTUREDBOX_H
#define TEXTUREDBOX_H

#include "Box.h"
#include "GraphicsEngine.h"

class TexturedBox : public Box
{
    public:
        TexturedBox(GraphicsEngine *ge, glm::vec2 c, GLfloat w, GLfloat h, GLuint tex, glm::vec4 uvs = {0, 0, 1, 1});
        virtual ~TexturedBox();

        virtual void refresh() override;
        virtual void draw() override;

    protected:
    private:
        glm::vec4 uvs;
        GLuint texId;
        GraphicsEngine *ge;
};

#endif // TEXTUREDBOX_H
