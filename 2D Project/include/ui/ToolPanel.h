#ifndef TOOLPANEL_H
#define TOOLPANEL_H

#include <algorithm>

#include "render/Box.h"
#include "ButtonTool.h"
#include "TexturedBox.h"

class ButtonTool;

class ToolPanel : public Drawable, public Listener
{
public:
    ToolPanel(GraphicsEngine *ge, int x, int y);
    virtual ~ToolPanel() {};

    virtual bool contains(glm::vec2 point) override { return false; };

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
