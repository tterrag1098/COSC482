#include "ToolPanel.h"

ToolPanel::ToolPanel(int x, int y) : Drawable(false), pos({x, y})
{
    bg = new Box(pos, 0, 0, {0, 0, 0, 0.75});
}

void ToolPanel::refresh()
{
    for (ButtonTool *b : buttons)
    {
        b->load();
    }
    bg->load();
}

void ToolPanel::draw() const
{
    bg->draw();
    for (ButtonTool *b : buttons)
    {
        b->draw();
    }
}

void ToolPanel::addButton(Tool* tool)
{
    int x = pos.x + padding + (buttons.size() % 2) * (butSize + padding);
    int y = pos.y + padding + ((butSize + padding) * (buttons.size() / 2));
    ButtonTool *button = new ButtonTool(x, y, butSize, tool);

    buttons.push_back(button);

    bg->setWidth(padding + ((butSize + padding) * std::min((int) buttons.size(), 2)));
    bg->setHeight(padding + ((butSize + padding) * (buttons.size() / 2)));

    load();
}

bool ToolPanel::mousePressed(ListenerContext<sf::Event::MouseButtonEvent> ctx)
{
    for (ButtonTool *b : buttons)
    {
        if (b->mousePressed(ctx))
        {
            return true;
        }
    }
    return false;
}

bool ToolPanel::mouseReleased(ListenerContext<sf::Event::MouseButtonEvent> ctx)
{
    for (ButtonTool *b : buttons)
    {
        if (b->mouseReleased(ctx))
        {
            return true;
        }
    }
    return false;
}

bool ToolPanel::mouseMoved(ListenerContext<sf::Event::MouseMoveEvent> ctx)
{
    for (ButtonTool *b : buttons)
    {
        if (b->mouseMoved(ctx))
        {
            return true;
        }
    }
    return false;
}
