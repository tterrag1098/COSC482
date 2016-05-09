#include "ToolEllipse.h"
#include "UI.h"
#include "GraphicsEngine.h"
#include "Ellipse.h"

ToolEllipse::ToolEllipse() : Tool("Ellipse", 1, 1) {}

ToolEllipse::~ToolEllipse() {}

void ToolEllipse::deactivated()
{
    ellipse = NULL;
}

bool ToolEllipse::mousePressed(ListenerContext<sf::Event::MouseButtonEvent> ctx)
{
    if (ctx.event.button == sf::Mouse::Left)
    {
        ctx.getUI()->getEngine()->addObject(ellipse = new Ellipse({ctx.event.x, ctx.event.y}, ctx.getUI()->getThickness(), ctx.getUI()->getSelectedColor(), ctx.getUI()->optionState()));
        return true;
    }
    return false;
}

bool ToolEllipse::mouseMoved(ListenerContext<sf::Event::MouseMoveEvent> ctx)
{
    const UI *ui = ctx.getUI();
    if (ellipse && ui->isMouseDown())
    {
        glm::vec2 last = ui->prevMousePos();
        glm::vec2 cur = {ctx.event.x, ctx.event.y};
        ellipse->setCenter(last + ((cur - last) / 2.0f));
        ellipse->setRadii((cur.x - last.x) / 2, (cur.y - last.y) / 2);
        return true;
    }
    else
    {
        ellipse = NULL;
    }
    return false;
}
