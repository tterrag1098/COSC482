#include "FillButton.h"
#include "StateButton.h"
#include "Box.h"
#include "GraphicsEngine.h"

FillButton::FillButton(GraphicsEngine *ge) : ge(ge), width(180), height(50)
{
    Drawable::children.push_back(bg = new Box({0, 0}, width, height, {0, 0, 0, 0.75}));

    but = new StateButton(0, pos.y + 205, 20);

    Drawable::children.push_back(but);
    Listener::children.push_back(but);

    text.loadFont("assets/DroidSansMono.ttf");
    text.setFontSize(18);
    text.setColor(1, 1, 1, 1);

    resized(ge->getSize());
}

FillButton::~FillButton() {}

void FillButton::resized(sf::Vector2u size)
{
    pos = {size.x - width - 10, 175};
    bg->setCorner(pos);

    int sx = pos.x + (width / 2) - 64 - 5;
    but->setCorner({sx, but->getCorner().y});

    load();
}

void FillButton::draw()
{
    Drawable::draw();
    TextRendererTTF tr = text;

    std::string str = "Fill:";
    tr.setScreenSize(ge->getSize().x, ge->getSize().y);
    tr.draw(str, pos.x + (width / 2) - (tr.textWidth(str) / 2), ge->getSize().y - 178 - 18, 0);
}

bool FillButton::fill()
{
    return but->getState();
}

bool FillButton::mousePressed(ListenerContext<sf::Event::MouseButtonEvent> ctx)
{
    return Listener::mousePressed(ctx) || bg->contains({ctx.event.x, ctx.event.y});
}

bool FillButton::mouseReleased(ListenerContext<sf::Event::MouseButtonEvent> ctx)
{
    return Listener::mouseReleased(ctx) || bg->contains({ctx.event.x, ctx.event.y});
}
