#ifndef TOOLPANEL_H
#define TOOLPANEL_H

#include <algorithm>

#include "render/Box.h"
#include "ButtonTool.h"

class ButtonTool;

class ToolPanel : public Drawable, public Listener
{
public:
    ToolPanel(int x, int y);
    virtual ~ToolPanel() {};

    void addButton(Tool *tool);

    void refresh() override;
    void draw() const override;

    bool mousePressed(ListenerContext<sf::Event::MouseButtonEvent> ctx) override;
    bool mouseReleased(ListenerContext<sf::Event::MouseButtonEvent> ctx) override;
    bool mouseMoved(ListenerContext<sf::Event::MouseMoveEvent> ctx) override;

protected:
private:
    glm::vec2 pos;
    Box *bg;

    std::vector<ButtonTool*> buttons;

    const int padding = 3;
    const int butSize = 22;
};

#endif // TOOLPANEL_H
