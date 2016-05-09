#ifndef TOOLELLIPSE_H
#define TOOLELLIPSE_H

#include "Tool.h"

class Ellipse;

class ToolEllipse : public Tool
{
public:
    ToolEllipse();
    virtual ~ToolEllipse();

    void deactivated() override;

    bool mousePressed(ListenerContext<sf::Event::MouseButtonEvent> ctx) override;
    bool mouseMoved(ListenerContext<sf::Event::MouseMoveEvent> ctx) override;

    bool hasOption() const override { return true; };
    std::string getOptionName() const override { return "Fill"; };

protected:
private:
    Ellipse *ellipse;
};
#endif // TOOLELLIPSE_H
