#include "TexturedBox.h"

TexturedBox::TexturedBox(GraphicsEngine *ge, glm::vec2 c, GLfloat w, GLfloat h, GLuint tex, glm::vec4 uvs) : Box(c, w, h), ge(ge), texId(tex), uvs(uvs) {}

TexturedBox::~TexturedBox() {}

void TexturedBox::refresh()
{
    vert({corner.x, corner.y + height}, color, {uvs.x, uvs.w});
    vert({corner.x + width, corner.y + height}, color, {uvs.z, uvs.w});
    vert({corner.x + width, corner.y}, color, {uvs.z, uvs.y});
    vert({corner.x, corner.y}, color, {uvs.x, uvs.y});

    index_quad(1);
}

void TexturedBox::draw()
{
    ge->activateTexture(texId);
    Box::draw();
    ge->activateTexture(-1);
}