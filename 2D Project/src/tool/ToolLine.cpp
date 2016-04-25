#include "ToolLine.h"

void ToolLine::deactivated()
{
    lastLine = NULL;
}

bool ToolLine::mousePressed(ListenerContext<sf::Event::MouseButtonEvent> ctx)
{
    if (ctx.event.button == sf::Mouse::Left)
    {
        glm::vec2 pos = {ctx.event.x, ctx.event.y};
        ctx.getUI()->getEngine()->addObject(lastLine = new LineSeg(pos, pos, ctx.getUI()->getSelectedColor()));
        return true;
    }
    return false;
}

bool ToolLine::mouseMoved(ListenerContext<sf::Event::MouseMoveEvent> ctx)
{
    const UI *ui = ctx.getUI();
    if (lastLine && ui->isMouseDown())
    {
        glm::vec2 cur = {ctx.event.x, ctx.event.y};
        lastLine->setPos2(cur);
        return true;
    }
    else
    {
        lastLine = NULL;
    }
    return false;
}
