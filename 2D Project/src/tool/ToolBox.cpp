#include "tool/ToolBox.h"

ToolBox::ToolBox() : Tool("Box")
{
    lastBox = NULL;
}

ToolBox::~ToolBox() {}

void ToolBox::deactivated()
{
    lastBox = NULL;
}

bool ToolBox::mousePressed(ListenerContext<sf::Event::MouseButtonEvent> ctx)
{
    if (ctx.event.button == sf::Mouse::Left)
    {
        ctx.getUI()->getEngine()->addObject(lastBox = new Box({ctx.event.x, ctx.event.y}, 0, 0, {rand_float(), rand_float(), rand_float(), 1}));
        return true;
    }
    return false;
}

bool ToolBox::mouseMoved(ListenerContext<sf::Event::MouseMoveEvent> ctx)
{
    const UI *ui = ctx.getUI();
    if (lastBox && ui->isMouseDown())
    {
        glm::vec2 last = ui->prevMousePos();
        glm::vec2 cur = {ctx.event.x, ctx.event.y};
        lastBox->setWidth(cur.x - last.x);
        lastBox->setHeight(cur.y - last.y);
        return true;
    }
    return false;
}
