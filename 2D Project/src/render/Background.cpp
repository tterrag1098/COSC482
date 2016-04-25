#include "Background.h"

Background::Background(GraphicsEngine *ge) : Box({0, 0}, 0, 0), ge(ge), texW(16), texH(16) {}

void Background::refresh()
{
    Box::refresh();

    uvs.clear();
    uvs.push_back({0, height / texH});
    uvs.push_back({width / texW, height / texH});
    uvs.push_back({width / texW, 0});
    uvs.push_back({0, 0});
}

void Background::draw()
{
    glUniform1i(ge->useTextureLoc, 1);
    Box::draw();
    glUniform1i(ge->useTextureLoc, 0);
}
