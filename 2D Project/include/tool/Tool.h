#ifndef TOOL_H
#define TOOL_H

#include <string>

#include "ui/Listeners.h"
#include "util/utils.h"

class Tool : public Listener
{
public:
    Tool(std::string name, int iconX, int iconY) : name(name), iconPos({iconX, iconY}) {};
    virtual ~Tool() {};

    virtual void activated() {};
    virtual void deactivated() {};

    std::string getName() { return name; }
    glm::ivec2 getIconPos() { return iconPos; }

private:
    std::string name;
    glm::ivec2 iconPos;
};

#endif // TOOL_H
