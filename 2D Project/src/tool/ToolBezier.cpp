#include "ToolBezier.h"
#include "UI.h"
#include "GraphicsEngine.h"
#include "BezierCurve.h"

ToolBezier::ToolBezier() : Tool("Bezier", 0, 1)
{
    curve = NULL;
    controlSet = false;
}

ToolBezier::~ToolBezier() {}

bool ToolBezier::mousePressed(ListenerContext<sf::Event::MouseButtonEvent> ctx)
{
    if (ctx.event.button == sf::Mouse::Left)
    {
        glm::vec2 pos = {ctx.event.x, ctx.event.y};
        if (!curve)
        {
            ctx.getUI()->getEngine()->addObject(curve = new BezierCurve(ctx.getUI()->getThickness(), pos, ctx.getUI()->getSelectedColor()));
            curve->setControl(pos);
            curve->setEnd(pos);
        }
        else if (!controlSet)
        {
            curve->setControl(pos);
            controlSet = true;
        }
        else
        {
            curve->setEnd(pos);
            curve = NULL;
            if (ctx.getUI()->optionState())
            {
                mousePressed(ctx);
                controlSet = false;
            }
        }
    }
    else if (ctx.event.button == sf::Mouse::Right && curve)
    {
        ctx.getUI()->getEngine()->removeObject(curve);
        curve = NULL;
    }
}

bool ToolBezier::mouseReleased(ListenerContext<sf::Event::MouseButtonEvent> ctx)
{
    if (!curve && controlSet)
    {
        controlSet = false;
        return true;
    }
    else if (curve)
    {
        return true;
    }
}

bool ToolBezier::mouseMoved(ListenerContext<sf::Event::MouseMoveEvent> ctx)
{
    if (curve)
    {
        glm::vec2 pos = {ctx.event.x, ctx.event.y};
        if (!controlSet)
        {
            curve->setControl(pos);
        }
        curve->setEnd(pos);
    }
}
