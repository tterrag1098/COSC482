#ifndef TOOLBEZIER_H
#define TOOLBEZIER_H

#include "Tool.h"

class BezierCurve;

class ToolBezier : public Tool
{
public:
    ToolBezier();
    virtual ~ToolBezier();

    bool mousePressed(ListenerContext<sf::Event::MouseButtonEvent> ctx) override;
    bool mouseReleased(ListenerContext<sf::Event::MouseButtonEvent> ctx) override;
    bool mouseMoved(ListenerContext<sf::Event::MouseMoveEvent> ctx) override;

    bool hasOption() const override { return true; };
    std::string getOptionName() const override { return "Path"; };

protected:
private:
    BezierCurve *curve;
    bool controlSet;
};

#endif // TOOLBEZIER_H
