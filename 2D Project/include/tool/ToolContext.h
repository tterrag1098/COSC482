#ifndef TOOLCONTEXT_H
#define TOOLCONTEXT_H

#include "core/UI.h"

class UI;

template <typename T>
class ToolContext
{
public:
    ToolContext(UI *ui, T e) : ui(ui), event(e) {};
    virtual ~ToolContext() {};

    const UI *ui;
    const T event;
protected:


private:
};

template<typename T>
inline ToolContext<T> create_ctx(UI *ui, T event)
{
    return ToolContext<T>(ui, event);
}

#endif // TOOLCONTEXT_H
