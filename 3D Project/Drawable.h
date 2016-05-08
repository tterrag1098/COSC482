#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "ProgramDefines.h"
#include "Material.h"

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

    virtual glm::mat4 getModelMat();

    Material getMaterial();
    int getLight();
    void assignLight(GLuint lightID);

protected:
    Drawable(Material mat, bool visible = true);

    std::vector<Drawable*> children;

private:
    bool visible;
    Material material;
    int light = -1;
};

#endif // DRAWABLE_H
