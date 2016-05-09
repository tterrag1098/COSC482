#include "OptionButton.h"
#include "StateButton.h"
#include "Box.h"
#include "UI.h"
#include "TexturedBox.h"
#include "GraphicsEngine.h"
#include "Tool.h"

OptionButton::OptionButton(UI *ui) : ui(ui), ge(ui->getEngine()), width(180), height(30)
{
    Drawable::children.push_back(bg = new Box({0, 0}, width, height, {0, 0, 0, 0.75}));

    but = new StateButton(0, 245, 20);

    Drawable::children.push_back(but);
    Listener::children.push_back(but);

    text.loadFont("assets/DroidSansMono.ttf");
    text.setFontSize(18);
    text.setColor(1, 1, 1, 1);

    texId = ge->loadTexture("assets/fillbutton.png");

    iconOn  = new TexturedBox(ge, {0, 245}, 20, 20, texId, {0, 0, 0.5f, 1});
    iconOff = new TexturedBox(ge, {0, 245}, 20, 20, texId, {0.5f, 0, 1, 1});

    resized(ge->getSize());
}

OptionButton::~OptionButton() {}

void OptionButton::resized(sf::Vector2u size)
{
    pos = {size.x - width - 10, 240};
    bg->setCorner(pos);

    int sx = pos.x + (width - 75);
    but->setCorner({sx, but->getCorner().y});
    iconOn->setCorner({sx, iconOn->getCorner().y});
    iconOff->setCorner({sx, iconOff->getCorner().y});

    load();
}

void OptionButton::refresh()
{
    iconOn->load();
    iconOff->load();
}

void OptionButton::draw()
{
    if (ui->getTool()->hasOption())
    {
        Drawable::draw();
        TextRendererTTF tr = text;

        std::string str = ui->getTool()->getOptionName() + ":";
        tr.setScreenSize(ge->getSize().x, ge->getSize().y);
        tr.draw(str, pos.x + 75 - (tr.textWidth(str) / 2), ge->getSize().y - 243 - 18, 0);

        glUseProgram(GraphicsEngine::defaultShader);

        but->getState() ? iconOn->draw() : iconOff->draw();
    }
}

bool OptionButton::state()
{
    return but->getState();
}

bool OptionButton::mousePressed(ListenerContext<sf::Event::MouseButtonEvent> ctx)
{
    return ui->getTool()->hasOption() && (Listener::mousePressed(ctx) || bg->contains({ctx.event.x, ctx.event.y}));
}

bool OptionButton::mouseReleased(ListenerContext<sf::Event::MouseButtonEvent> ctx)
{
    return ui->getTool()->hasOption() && (Listener::mouseReleased(ctx) || bg->contains({ctx.event.x, ctx.event.y}));
}
