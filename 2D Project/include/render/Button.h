#ifndef BUTTON_H
#define BUTTON_H

#include "Drawable.h"
#include "util/utils.h"

class Button : public Drawable
{
public:
    Button(int x, int y, int size) : Button({x, y}, size) {};
    Button(glm::vec2 pos, int size) : Drawable(true), pos(pos), size(size) {};
    virtual ~Button() {};

protected:
    void refresh() override;

private:
    glm::vec2 pos;
    int size;
};

#endif // BUTTON_H
