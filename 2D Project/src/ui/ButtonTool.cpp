#include "ui/ButtonTool.h"

bool ButtonTool::mousePressed(ListenerContext<sf::Event::MouseButtonEvent> ctx)
{
    if (Button::mousePressed(ctx))
    {
        ctx.getUI()->setToolActive(tool);
        return true;
    }
    return false;
}
