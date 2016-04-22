#include "ui/Button.h"

using namespace glm;

void Button::refresh()
{
    vec4 col_center = {0.15f, 0.15f, 0.15f, 1};
    vec4 col_light =  {0.3f, 0.3f, 0.3f, 1};
    vec4 col_dark = BLACK;

    if (pressed)
    {
        vec4 temp = col_light;
        col_light = col_dark;
        col_dark = temp;
    }

    int in = size / 10;

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
