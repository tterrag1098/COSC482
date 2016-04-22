#ifndef TOOLLINE_H
#define TOOLLINE_H

#include "Tool.h"
#include "LineSeg.h"
#include "ui/UI.h"

class ToolLine : public Tool
{
    public:
        ToolLine() : Tool("Line"){};
        virtual ~ToolLine(){};

        void deactivated() override;

        bool mousePressed(ListenerContext<sf::Event::MouseButtonEvent> ctx) override;
        bool mouseMoved(ListenerContext<sf::Event::MouseMoveEvent> ctx) override;

    protected:
    private:

        LineSeg *lastLine = NULL;
};

#endif // TOOLLINE_H
