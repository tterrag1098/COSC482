#ifndef TOOLBOX_H
#define TOOLBOX_H

#include "Tool.h"

class Box;

class ToolBox : public Tool
{
public:
    ToolBox();
    virtual ~ToolBox();

    void deactivated() override;

    bool mousePressed(ListenerContext<sf::Event::MouseButtonEvent> ctx) override;
    bool mouseMoved(ListenerContext<sf::Event::MouseMoveEvent> ctx) override;

    bool hasOption() const override { return true; };
    std::string getOptionName() const override { return "Fill"; };

protected:
private:
    Box *lastBox;
};

#endif // TOOLBOX_H
