#ifndef TOOLBOX_H
#define TOOLBOX_H

#include "tool/Tool.h"
#include "render/Box.h"

class ToolBox : public Tool
{
    public:
        ToolBox();
        virtual ~ToolBox();

        void deactivated() override;

        void mousePressed(ToolContext<sf::Event::MouseButtonEvent> ctx) override;
        void mouseMoved(ToolContext<sf::Event::MouseMoveEvent> ctx) override;

    protected:
    private:
        Box *lastBox;
};

#endif // TOOLBOX_H
