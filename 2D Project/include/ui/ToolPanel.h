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

protected:
private:
    glm::vec2 pos;
    Box *bg;
    int buttons;

    const int padding = 3;
    const int butSize = 22;
};

#endif // TOOLPANEL_H
