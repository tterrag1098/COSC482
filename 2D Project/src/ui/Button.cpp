#include "Button.h"
#include "util/utils.h"

using namespace glm;

void Button::refresh()
{
    vec4 col_center = {0.2f, 0.2f, 0.2f, 1};
    vec4 col_light =  {0.4f, 0.4f, 0.4f, 1};
    vec4 col_dark = BLACK;

    if (pressed)
    {
        vec4 temp = col_light;
        col_light = col_dark;
        col_dark = temp;
    }

    int in = 2 + (size / 12);

    vert(pos, col_light);
    vert(pos + vec2(in, in), col_light);
    vert(pos + vec2(size - in, in), col_light);
    vert(pos + vec2(size, 0), col_light);

    vert(pos + vec2(size, 0), col_light);
    vert(pos + vec2(size - in, in), col_light);
    vert(pos + vec2(size - in, size - in), col_light);
    vert(pos + vec2(size, size), col_light);

    vert(pos + vec2(size, size), col_dark);
    vert(pos + vec2(size - in, size - in), col_dark);
    vert(pos + vec2(in, size - in), col_dark);
    vert(pos + vec2(0, size), col_dark);

    vert(pos + vec2(0, size), col_dark);
    vert(pos + vec2(in, size - in), col_dark);
    vert(pos + vec2(in, in), col_dark);
    vert(pos, col_dark);

    vert(pos + vec2(in, in), col_center);
    vert(pos + vec2(size - in, in), col_center);
    vert(pos + vec2(size - in, size - in), col_center);
    vert(pos + vec2(in, size - in), col_center);

    index_quad(5);
}

bool Button::mousePressed(ListenerContext<sf::Event::MouseButtonEvent> ctx)
{
    if (ctx.event.x > pos.x && ctx.event.x < pos.x + size && ctx.event.y > pos.y && ctx.event.y < pos.y + size)
    {
        pressed = true;
        load();
        return true;
    }
    return false;
}

bool Button::mouseReleased(ListenerContext<sf::Event::MouseButtonEvent> ctx)
{
    if (pressed)
    {
        pressed = false;
        load();
        return true;
    }
    return false;
}

void Button::setCorner(glm::vec2 p)
{
    pos = p;
    load();
}

void Button::setPressed(bool p)
{
    pressed = p;
    load();
}

glm::vec2 Button::getCorner()
{
    return pos;
}

int Button::getSize()
{
    return size;
}

bool Button::contains(glm::vec2 p)
{
    bool ret = p.x > pos.x && p.x < pos.x + size && p.y > pos.y && p.y < pos.y + size;
    return ret;
}
