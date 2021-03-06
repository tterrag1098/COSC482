#ifndef BACKGROUND_H_INCLUDED
#define BACKGROUND_H_INCLUDED

#include "render/Box.h"

class GraphicsEngine;

class Background : public Box
{
public:
    Background(GraphicsEngine *ge);

    void refresh() override;
    void draw() override;

protected:

private:
    GraphicsEngine *ge;
    int texW, texH;
    GLuint texId;
};

#endif // BACKGROUND_H_INCLUDED
