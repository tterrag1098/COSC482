#include "ui/ButtonTool.h"
#include "UI.h"

bool ButtonTool::mousePressed(ListenerContext<sf::Event::MouseButtonEvent> ctx)
{
    if (Button::mousePressed(ctx))
    {
        ctx.getUI()->setToolActive(tool);
        return true;
    }

    if (pressed && ctx.getUI()->getTool() != tool)
    {
        pressed = false;
        load();
    }
    return false;
}

bool ButtonTool::mouseReleased(ListenerContext<sf::Event::MouseButtonEvent> ctx)
{
    bool ret = Button::mouseReleased(ctx);
    if (ctx.getUI()->getTool() == tool)
    {
        pressed = true;
        load();
    }
    return ret;
}
