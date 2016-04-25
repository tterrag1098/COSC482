#include "ToolPanel.h"

ToolPanel::ToolPanel(int x, int y) : Drawable(false), pos({x, y}), buttons(0)
{
    bg = new Box(pos, 0, 0, {0, 0, 0, 0.75});
    Drawable::children.push_back(bg);
}

void ToolPanel::addButton(Tool* tool)
{
    int x = pos.x + padding + (buttons % 2) * (butSize + padding);
    int y = pos.y + padding + ((butSize + padding) * (buttons / 2));
    ButtonTool *button = new ButtonTool(x, y, butSize, tool);

    Drawable::children.push_back(button);
    Listener::children.push_back(button);

    buttons++;

    bg->setWidth(padding + ((butSize + padding) * std::min(buttons, 2)));
    bg->setHeight(padding + ((butSize + padding) * ((buttons + 1) / 2)));

    load();
}

