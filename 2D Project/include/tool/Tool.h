#ifndef TOOL_H
#define TOOL_H

#include <string>

#include "ui/Listeners.h"
#include "glm/glm.hpp"

class Tool : public Listener
{
public:
    Tool(std::string name, int iconX, int iconY) : name(name), iconPos({iconX, iconY}) {};
    virtual ~Tool() {};

    virtual void activated() {};
    virtual void deactivated() {};

    virtual bool hasOption() const { return false; };
    virtual std::string getOptionName() const { return ""; };

    std::string getName() { return name; }
    glm::ivec2 getIconPos() { return iconPos; }

private:
    std::string name;
    glm::ivec2 iconPos;
};

#endif // TOOL_H
