#include "ToolPanel.h"
#include "GraphicsEngine.h"
#include "Tool.h"
#include "Box.h"
#include "ButtonTool.h"
#include "TexturedBox.h"

ToolPanel::ToolPanel(GraphicsEngine *ge, int x, int y) : Drawable(false), ge(ge), pos({x, y}), buttons(0)
{
    bg = new Box(pos, 0, 0, {0, 0, 0, 0.75});
    Drawable::children.push_back(bg);

    texId = ge->loadTexture("assets/tools.png");
}

void ToolPanel::addButton(Tool* tool, bool currentTool)
{
    int x = pos.x + padding + (buttons % 2) * (butSize + padding);
    int y = pos.y + padding + ((butSize + padding) * (buttons / 2));
    glm::vec2 iconPos = glm::vec2(tool->getIconPos()) / 4.0f;

    ButtonTool *button = new ButtonTool(x, y, butSize, tool);
    button->setPressed(currentTool);
    TexturedBox *icon = new TexturedBox(ge, {x, y}, butSize, butSize, texId, {iconPos.x, iconPos.y, iconPos.x + 0.25f, iconPos.y + 0.25f});

    Drawable::children.push_back(button);
    Listener::children.push_back(button);

    Drawable::children.push_back(icon);

    buttons++;

    bg->setWidth(padding + ((butSize + padding) * std::min(buttons, 2)));
    bg->setHeight(padding + ((butSize + padding) * ((buttons + 1) / 2)));

    load();
}

bool ToolPanel::mousePressed(ListenerContext<sf::Event::MouseButtonEvent> ctx)
{
    return Listener::mousePressed(ctx) || bg->contains({ctx.event.x, ctx.event.y});
}

bool ToolPanel::mouseReleased(ListenerContext<sf::Event::MouseButtonEvent> ctx)
{
    return Listener::mouseReleased(ctx) || bg->contains({ctx.event.x, ctx.event.y});
}
