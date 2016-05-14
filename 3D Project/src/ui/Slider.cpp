#include "Slider.h"
#include "Box.h"
#include "Button.h"
#include "UI.h"

Slider::Slider(int x, int y, int width, int min, int max, glm::vec4 color) : Drawable(false), width(width), min(min), max(max), dragging(false)
{
    bar = new Box({x, y}, width + 10, 10, color);
    thumb = new Button({x, y}, 10);

    Drawable::children.push_back(bar);

    Listener::children.push_back(thumb);
    Drawable::children.push_back(thumb);

    setValue(min);
}

Slider::~Slider()
{
    //dtor
}

int Slider::getValue()
{
    return pos;
}

void Slider::setX(int x)
{
    glm::vec2 tcorner = thumb->getCorner();
    glm::vec2 bcorner = bar->getCorner();

    int off = tcorner.x - bcorner.x;

    tcorner.x = x + off;
    bcorner.x = x;

    thumb->setCorner(tcorner);
    bar->setCorner(bcorner);
}

void Slider::setValue(int value)
{
    pos = value;
    glm::vec2 corner = thumb->getCorner();
    corner.x = bar->getCorner().x + (pos / (max - min)) * width;
    thumb->setCorner(corner);
}

bool Slider::mousePressed(ListenerContext<sf::Event::MouseButtonEvent> ctx)
{
    bool pressed = Listener::mousePressed(ctx);
    if (!pressed && bar->contains({ctx.event.x, ctx.event.y}))
    {
        thumb->setCorner({ctx.event.x - (thumb->getWidth() / 2), thumb->getCorner().y});
        calculateValue();
        thumb->setPressed(true);
        pressed = true;
    }
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
        glm::vec2 lastPos = ctx.getUI()->getPrevMouseClick();
        glm::vec2 corner = thumb->getCorner();
        float move = pressPos.x + (mouse.x - lastPos.x);
        corner.x = std::max(bar->getCorner().x, std::min(move, bar->getCorner().x + bar->getWidth() - thumb->getWidth()));
        calculateValue();
        thumb->setCorner(corner);
        return true;
    }
    return false;
}

void Slider::calculateValue()
{
    pos = (thumb->getCorner().x - bar->getCorner().x) * ((float) (max - min) / width);
    pos += min;
}
