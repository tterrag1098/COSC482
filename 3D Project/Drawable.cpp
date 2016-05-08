#include "Drawable.h"

Drawable::Drawable(Material mat, bool visible) : material(mat), visible(visible) {}

Drawable::~Drawable()
{
    for (Drawable *d : children)
    {
        delete d;
    }
}

void Drawable::load()
{
    for (Drawable *d : children)
    {
        d->load();
    }
}

void Drawable::draw(glm::mat4 pvm)
{
    for (Drawable *d : children)
    {
        d->draw(pvm);
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

int Drawable::getLight()
{
    return light;
}
