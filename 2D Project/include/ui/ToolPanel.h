#ifndef TOOLPANEL_H
#define TOOLPANEL_H

#include <algorithm>

#include "Drawable.h"
#include "Listeners.h"

class GraphicsEngine;
class ButtonTool;
class Tool;
class Box;

class ToolPanel : public Drawable, public Listener
{
public:
    ToolPanel(GraphicsEngine *ge, int x, int y);
    virtual ~ToolPanel() {};

    virtual bool contains(glm::vec2 point) override { return false; };

    bool mousePressed(ListenerContext<sf::Event::MouseButtonEvent> ctx) override;
    bool mouseReleased(ListenerContext<sf::Event::MouseButtonEvent> ctx) override;

    void addButton(Tool *tool);

protected:
private:
    GraphicsEngine *ge;
    glm::vec2 pos;
    Box *bg;
    int buttons;
    GLuint texId;

    const int padding = 3;
    const int butSize = 22;
};

#endif // TOOLPANEL_H
