#include "ThicknessSlider.h"
#include "Box.h"
#include "GraphicsEngine.h"
#include "Slider.h"

ThicknessSlider::ThicknessSlider(GraphicsEngine *ge) : ge(ge), width(180), height(50)
{
    Drawable::children.push_back(bg = new Box({0, 0}, width, height, {0, 0, 0, 0.75}));

    thickness = new Slider(0, pos.y + 205, 128, 1, 64);

    Drawable::children.push_back(thickness);
    Listener::children.push_back(thickness);

    text.loadFont("assets/DroidSansMono.ttf");
    text.setFontSize(18);
    text.setColor(1, 1, 1, 1);

    resized(ge->getSize());
}

ThicknessSlider::~ThicknessSlider() {}

void ThicknessSlider::resized(sf::Vector2u size)
{
    pos = {size.x - width - 10, 175};
    bg->setCorner(pos);

    int sx = pos.x + (width / 2) - 64 - 5;
    thickness->setX(sx);

    load();
}

void ThicknessSlider::draw()
{
    Drawable::draw();
    TextRendererTTF tr = text;

    tr.setScreenSize(ge->getSize().x, ge->getSize().y);

    char str[3];
    sprintf(str, "Thickness:%d", thickness->getValue());
    tr.draw(str, pos.x + (width / 2) - (tr.textWidth(str) / 2), ge->getSize().y - 178 - 18, 0);

    glUseProgram(GraphicsEngine::defaultShader);
}

int ThicknessSlider::getThickness()
{
    return thickness->getValue();
}

bool ThicknessSlider::mousePressed(ListenerContext<sf::Event::MouseButtonEvent> ctx)
{
    return Listener::mousePressed(ctx) || bg->contains({ctx.event.x, ctx.event.y});
}

bool ThicknessSlider::mouseReleased(ListenerContext<sf::Event::MouseButtonEvent> ctx)
{
    return Listener::mouseReleased(ctx) || bg->contains({ctx.event.x, ctx.event.y});
}
