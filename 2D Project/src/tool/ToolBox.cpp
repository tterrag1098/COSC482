#include "ToolBox.h"

ToolBox::ToolBox() : Tool("Box") {}

ToolBox::~ToolBox() {}

void ToolBox::deactivated()
{
    lastBox = NULL;
}

void ToolBox::mousePressed(ToolContext<sf::Event::MouseButtonEvent> ctx)
{
    if (ctx.event.button == sf::Mouse::Left)
    {
        glm::vec2 sc = ctx.ui->toScreenCoords({ctx.event.x, ctx.event.y});
        ctx.ui->getEngine()->addObject(lastBox = new Box({sc.x, sc.y}, 0, 0, {rand_float(), rand_float(), rand_float()}));
    }
}

void ToolBox::mouseMoved(ToolContext<sf::Event::MouseMoveEvent> ctx)
{
    const UI *ui = ctx.ui;
    if (lastBox && ui->isMouseDown())
    {
        glm::vec2 last = ui->toScreenCoords(ui->prevMousePos());
        glm::vec2 cur = ui->toScreenCoords({ctx.event.x, ctx.event.y});
        lastBox->setWidth(cur.x - last.x);
        lastBox->setHeight(-cur.y + last.y);
    }
}
