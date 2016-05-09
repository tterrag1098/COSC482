#include "Background.h"
#include "GraphicsEngine.h"

Background::Background(GraphicsEngine *ge) : Box({0, 0}, 0, 0), ge(ge), texW(16), texH(16)
{
    texId = ge->loadTexture("assets/bg.png"); // WARNING this could break if used more than once. Currently only used for color picker.
}

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
    ge->activateTexture(texId);
    Box::draw();
    ge->activateTexture(-1);
}
