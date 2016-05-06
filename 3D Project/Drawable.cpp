#include "Drawable.h"

Drawable::Drawable(bool visible) : visible(visible) {}

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

