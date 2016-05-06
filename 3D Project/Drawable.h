#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "ProgramDefines.h"

#include <GL/glew.h>

#include <SFML/System/Vector2.hpp>

#include <glm/glm.hpp>

#include <vector>

class Drawable
{
public:
    virtual ~Drawable();

    virtual void draw(glm::mat4 pvm);

    virtual void load();

protected:
    Drawable(bool visible = true);

    std::vector<Drawable*> children;

private:
    bool visible;
};

#endif // DRAWABLE_H
