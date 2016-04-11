#ifndef TOOLBOX_H
#define TOOLBOX_H

#include "core/Listeners.h"
#include "core/UI.h"
#include "tool/Tool.h"
#include "render/Box.h"

class ToolBox : public Tool
{
    public:
        ToolBox();
        virtual ~ToolBox();

        void deactivated() override;

        void mousePressed(ListenerContext<sf::Event::MouseButtonEvent> ctx) override;
        void mouseMoved(ListenerContext<sf::Event::MouseMoveEvent> ctx) override;

    protected:
    private:
        Box *lastBox;
};

#endif // TOOLBOX_H
