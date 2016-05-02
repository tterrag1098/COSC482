#include "ColorPicker.h"

ColorPicker::ColorPicker(GraphicsEngine *ge) : ge(ge), width(180), height(150)
{
    Drawable::children.push_back(bg = new Box({0, 0}, width, height, {0, 0, 0, 0.75}));

    int colorw = 120;
    int colorh = 30;

    colorbg = new Background(ge);
    colorbg->setWidth(colorw);
    colorbg->setHeight(colorh);
    colorbg->setCorner({0, 0});

    Drawable::children.push_back(colorbg);

    color = new Box({0, 0}, colorw, colorh);

    Drawable::children.push_back(color);

    r = new Slider(0, pos.y + 35, 128, 0, 255);
    g = new Slider(0, pos.y + 55, 128, 0, 255);
    b = new Slider(0, pos.y + 75, 128, 0, 255);
    a = new Slider(0, pos.y + 95, 128, 0, 255);
    a->setValue(255);

    Drawable::children.push_back(r);
    Drawable::children.push_back(g);
    Drawable::children.push_back(b);
    Drawable::children.push_back(a);

    Listener::children.push_back(r);
    Listener::children.push_back(g);
    Listener::children.push_back(b);
    Listener::children.push_back(a);

    text.loadFont("assets/DroidSansMono.ttf");
    text.setFontSize(18);
    text.setColor(1, 1, 1, 1);

    resized(ge->getSize());
}

ColorPicker::~ColorPicker()
{
    //dtor
}

bool ColorPicker::contains(glm::vec2 point)
{
    return false;
}

void ColorPicker::resized(sf::Vector2u size)
{
    pos = {size.x - width - 10, 10};

    bg->setCorner(pos);

    glm::vec2 colorpos = {pos.x + 30, pos.y + 110};

    colorbg->setCorner(colorpos);
    color->setCorner(colorpos);

    int sx = pos.x + (width / 2) - 64 - 5;

    r->setX(sx);
    g->setX(sx);
    b->setX(sx);
    a->setX(sx);

    load();
}

void ColorPicker::draw()
{
    Drawable::draw();
    TextRendererTTF tr = text;

    tr.setScreenSize(ge->getSize().x, ge->getSize().y);

    glm::ivec4 col = {r->getValue(), g->getValue(), b->getValue(), a->getValue()};
    std::string str = "#" + int_to_hex(((col.r & 255) << 24) | ((col.g & 255) << 16) | ((col.b & 255) << 8) | (col.a & 255));
    tr.draw(str, pos.x + (width / 2) - (tr.textWidth(str) / 2), ge->getSize().y - 10 - 18, 0);

    if (col != prevColor)
    {
        prevColor = col;
        color->setColor(getColor());
    }

    glUseProgram(GraphicsEngine::defaultShader);
}

glm::vec4 ColorPicker::getColor()
{
    return glm::vec4(prevColor) / 255.0f;
}

bool ColorPicker::mousePressed(ListenerContext<sf::Event::MouseButtonEvent> ctx)
{
    return Listener::mousePressed(ctx) || bg->contains({ctx.event.x, ctx.event.y});
}

bool ColorPicker::mouseReleased(ListenerContext<sf::Event::MouseButtonEvent> ctx)
{
    return Listener::mouseReleased(ctx) || bg->contains({ctx.event.x, ctx.event.y});
}
