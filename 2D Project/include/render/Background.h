#ifndef BACKGROUND_H_INCLUDED
#define BACKGROUND_H_INCLUDED

#include "render/Box.h"

class Background : public Box
{
public:
    Background(int tw, int th) : Box({0, 0}, 0, 0), texW(tw), texH(th) {}

protected:
    void refresh() override
    {
        Box::refresh();

        uvs.clear();
        uvs.push_back({0, height / texH});
        uvs.push_back({width / texW, height / texH});
        uvs.push_back({width / texW, 0});
        uvs.push_back({0, 0});
    }

private:
    int texW, texH;
};

#endif // BACKGROUND_H_INCLUDED
