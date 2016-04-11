#ifndef LISTENERS_H_INCLUDED
#define LISTENERS_H_INCLUDED

#include <SFML/Window/Event.hpp>

#include "core/Listeners.h"

class UI;

template <typename T>
class ListenerContext
{
public:
    ListenerContext(UI *ui, T e) : ui(ui), event(e) {};
    virtual ~ListenerContext() {};

    const UI *ui;
    const T event;
protected:


private:
};

template<typename T>
inline ListenerContext<T> create_ctx(UI *ui, T event)
{
    return ListenerContext<T>(ui, event);
}

class Listener
{
public:
    virtual void mousePressed(ListenerContext<sf::Event::MouseButtonEvent> ctx) {};
    virtual void mouseReleased(ListenerContext<sf::Event::MouseButtonEvent> ctx) {};
    virtual void mouseMoved(ListenerContext<sf::Event::MouseMoveEvent> ctx) {};
};

#endif // LISTENERS_H_INCLUDED
