#ifndef TOOLDRAW_H
#define TOOLDRAW_H

#include "Tool.h"

class FreeformLine;

class ToolDraw : public Tool
{
public:
    ToolDraw();
    virtual ~ToolDraw();

    bool mousePressed(ListenerContext<sf::Event::MouseButtonEvent> ctx) override;
    bool mouseReleased(ListenerContext<sf::Event::MouseButtonEvent> ctx) override;
    bool mouseMoved(ListenerContext<sf::Event::MouseMoveEvent> ctx) override;

protected:
private:
    FreeformLine *curLine;
};

#endif // TOOLDRAW_H
