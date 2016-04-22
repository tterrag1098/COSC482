#ifndef BUTTONTOOL_H
#define BUTTONTOOL_H

#include <ui/Button.h>
#include <tool/Tool.h>
#include <ui/UI.h>

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
