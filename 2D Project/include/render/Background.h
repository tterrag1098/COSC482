#ifndef BACKGROUND_H_INCLUDED
#define BACKGROUND_H_INCLUDED

#include "render/Box.h"
#include "GraphicsEngine.h"

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
};

#endif // BACKGROUND_H_INCLUDED
