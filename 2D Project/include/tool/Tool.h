#ifndef TOOL_H
#define TOOL_H

#include <string>

#include "core/Listeners.h"

class Tool : public Listener
{
public:
    Tool(std::string) {};
    virtual ~Tool() {};

    virtual void activated() {};
    virtual void deactivated() {};

    std::string getName()
    {
        return name;
    };
private:

    std::string name;
};

#endif // TOOL_H
