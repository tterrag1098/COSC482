#ifndef BUTTONTOOL_H
#define BUTTONTOOL_H

#include "Button.h"

class Tool;

class ButtonTool : public Button
{
    public:
        ButtonTool(int x, int y, int size, Tool *tool) : Button(x, y, size), tool(tool){};
        virtual ~ButtonTool(){};

        bool mousePressed(ListenerContext<sf::Event::MouseButtonEvent> ctx) override;
    protected:
    private:
        Tool *tool;
};

#endif // BUTTONTOOL_H
