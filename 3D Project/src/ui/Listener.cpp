#include "Listeners.h"

Listener::~Listener()
{
    for (Listener *l : children) delete l;
}

bool Listener::mousePressed(ButtonContext ctx)
{
    bool res = false;
    for (Listener *l : children)
    {
        if (l->mousePressed(ctx))
        {
            res = true;
        }
    }
    return res;
}

bool Listener::mouseReleased(ButtonContext ctx)
{
    bool res = false;
    for (Listener *l : children)
    {
        if (l->mouseReleased(ctx))
        {
            res = true;
        }
    }
    return res;
}

bool Listener::mouseMoved(MoveContext ctx)
{
    bool res = false;
    for (Listener *l : children)
    {
        if (l->mouseMoved(ctx))
        {
            res = true;
        }
    }
    return res;
}

bool Listener::keyPressed(KeyContext ctx)
{
    bool res = false;
    for (Listener *l : children)
    {
        if (l->keyPressed(ctx))
        {
            res = true;
        }
    }
    return res;
}

bool Listener::keyInput(InputContext ctx)
{
    bool res = false;
    for (Listener *l : children)
    {
        if (l->keyInput(ctx))
        {
            res = true;
        }
    }
    return res;
}
