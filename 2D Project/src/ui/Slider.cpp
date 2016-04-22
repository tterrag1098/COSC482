#include "Slider.h"

Slider::Slider(int x, int y, int width, int min, int max) : Drawable(false), width(width), min(min), max(max), dragging(false)
{
    bar = new Box({x, y}, width + 10, 10);
    thumb = new Button({x, y}, 10);

    Drawable::children.push_back(bar);

    Listener::children.push_back(thumb);
    Drawable::children.push_back(thumb);
}

Slider::~Slider()
{
    //dtor
}

int Slider::getValue()
{
    return pos;
}

bool Slider::mousePressed(ListenerContext<sf::Event::MouseButtonEvent> ctx)
{
    bool pressed = Listener::mousePressed(ctx);
    if (pressed)
    {
        dragging = true;
        pressPos = thumb->getCorner();
        return true;
    }
    return false;
}

bool Slider::mouseReleased(ListenerContext<sf::Event::MouseButtonEvent> ctx)
{
    dragging = false;
    return Listener::mouseReleased(ctx);
}

bool Slider::mouseMoved(ListenerContext<sf::Event::MouseMoveEvent> ctx)
{
    if (dragging)
    {
        glm::vec2 mouse = {ctx.event.x, ctx.event.y};
        glm::vec2 lastPos = ctx.getUI()->prevMousePos();
        glm::vec2 corner = thumb->getCorner();
        float move = pressPos.x + (mouse.x - lastPos.x);
        corner.x = std::max(bar->getCorner().x, std::min(move, bar->getCorner().x + bar->getWidth() - thumb->getSize()));
        pos = (corner.x - bar->getCorner().x) * ((float) (max - min) / width);
        pos += min;
        std::cout << pos << std::endl;
        thumb->setCorner(corner);
        return true;
    }
    return false;
}
