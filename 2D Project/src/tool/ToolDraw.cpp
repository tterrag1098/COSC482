#include "ToolDraw.h"

ToolDraw::ToolDraw() : Tool("Draw")
{
    curLine = NULL;
}

ToolDraw::~ToolDraw()
{
    //dtor
}

bool ToolDraw::mousePressed(ListenerContext<sf::Event::MouseButtonEvent> ctx)
{
    if (ctx.event.button == sf::Mouse::Left)
    {
        glm::vec2 pos = {ctx.event.x, ctx.event.y};
        ctx.getUI()->getEngine()->addObject(curLine = new FreeformLine(ctx.getUI()->getSelectedColor()));
        curLine->newSegment(pos);
        return true;
    }
    return false;
}

bool ToolDraw::mouseMoved(ListenerContext<sf::Event::MouseMoveEvent> ctx)
{
    if (curLine && ctx.getUI()->isMouseDown())
    {
        glm::vec2 prev = curLine->currentPos();
        glm::vec2 pos = {ctx.event.x, ctx.event.y};
        if (glm::distance(prev, pos) > 3)
        {
            curLine->newSegment(pos);
        }
        return true;
    }
    return false;
}

bool ToolDraw::mouseReleased(ListenerContext<sf::Event::MouseButtonEvent> ctx)
{
    if (curLine)
    {
        curLine = NULL;
        return true;
    }
    return false;
}
