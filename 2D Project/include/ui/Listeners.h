#ifndef LISTENERS_H_INCLUDED
#define LISTENERS_H_INCLUDED

#include <SFML/Window/Event.hpp>

#include "ui/Listeners.h"

class UI;

template <typename T>
class ListenerContext
{
public:
    ListenerContext(UI *ui, T e) : ui(ui), event(e) {};
    virtual ~ListenerContext() {};

    const T event;
    UI* getUI() { return ui; }

protected:

private:
    UI *ui;
};

template<typename T>
inline ListenerContext<T> create_ctx(UI *ui, T event)
{
    return ListenerContext<T>(ui, event);
}

class Listener
{
public:
    virtual bool mousePressed(ListenerContext<sf::Event::MouseButtonEvent> ctx) { return false; };
    virtual bool mouseReleased(ListenerContext<sf::Event::MouseButtonEvent> ctx) { return false; };
    virtual bool mouseMoved(ListenerContext<sf::Event::MouseMoveEvent> ctx) { return false; };
};

#endif // LISTENERS_H_INCLUDED
