#ifndef TOOL_H
#define TOOL_H

#include <string>
#include <SFML/Window/Event.hpp>

#include "ToolContext.h"

class Tool
{
public:
    Tool(std::string) {};
    virtual ~Tool() {};

    virtual void activated() {};
    virtual void deactivated() {};

    virtual void mousePressed(ToolContext<sf::Event::MouseButtonEvent> ctx) {};
    virtual void mouseReleased(ToolContext<sf::Event::MouseButtonEvent> ctx) {};
    virtual void mouseMoved(ToolContext<sf::Event::MouseMoveEvent> ctx) {};

    std::string getName()
    {
        return name;
    };
private:

    std::string name;
};

#endif // TOOL_H
