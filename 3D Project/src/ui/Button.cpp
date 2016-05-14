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

    int in = 2 + (std::min(width, height) / 12);

    vert(pos, col_light);
    vert(pos + vec2(in, in), col_light);
    vert(pos + vec2(width - in, in), col_light);
    vert(pos + vec2(width, 0), col_light);

    vert(pos + vec2(width, 0), col_light);
    vert(pos + vec2(width - in, in), col_light);
    vert(pos + vec2(width - in, height - in), col_light);
    vert(pos + vec2(width, height), col_light);

    vert(pos + vec2(width, height), col_dark);
    vert(pos + vec2(width - in, height - in), col_dark);
    vert(pos + vec2(in, height - in), col_dark);
    vert(pos + vec2(0, height), col_dark);

    vert(pos + vec2(0, height), col_dark);
    vert(pos + vec2(in, height - in), col_dark);
    vert(pos + vec2(in, in), col_dark);
    vert(pos, col_dark);

    vert(pos + vec2(in, in), col_center);
    vert(pos + vec2(width - in, in), col_center);
    vert(pos + vec2(width - in, height - in), col_center);
    vert(pos + vec2(in, height - in), col_center);

    index_quad(5);
}

bool Button::mousePressed(ListenerContext<sf::Event::MouseButtonEvent> ctx)
{
    if (contains({ctx.event.x, ctx.event.y}))
    {
        setPressed(true);
        return true;
    }
    return false;
}

bool Button::mouseReleased(ListenerContext<sf::Event::MouseButtonEvent> ctx)
{
    if (pressed)
    {
        setPressed(false);
        return true;
    }
    return false;
}

bool Button::mouseMoved(ListenerContext<sf::Event::MouseMoveEvent> ctx)
{
    return pressed;
}

void Button::setCorner(glm::vec2 p)
{
    pos = p;
    load();
}

void Button::setPressed(bool p)
{
    if (p && pressed != p) fireCallbacks();
    pressed = p;
    load();
}

void Button::onPressed(std::function<void()>&& f)
{
    callbacks.push_back(f);
}

void Button::fireCallbacks()
{
    for (std::function<void()> f : callbacks)
    {
        f();
    }
}

glm::vec2 Button::getCorner()
{
    return pos;
}

int Button::getWidth()
{
    return width;
}

int Button::getHeight()
{
    return height;
}

bool Button::contains(glm::vec2 p)
{
    bool ret = p.x > pos.x && p.x < pos.x + width && p.y > pos.y && p.y < pos.y + height;
    return ret;
}
