#include "ui/UI.h"
#include "tool/ToolBox.h"
#include "ToolPanel.h"
#include "ColorPicker.h"
#include "ThicknessSlider.h"
#include "OptionButton.h"

#include "ToolDraw.h"
#include "ToolLine.h"
#include "ToolBox.h"
#include "ToolFill.h"
#include "ToolBezier.h"
#include "ToolEllipse.h"

#include "GraphicsEngine.h"

/**
\file UI.cpp
\brief User interface processor for the program.

\version   1.2
\date      Written: 3/22/2016  <BR> Revised: 4/1/2016

*/

/**
\brief Constructor

\param graph --- Pointer to the GraphicsEngine that this interface processor is attached.

Simply stores the pointer of the GraphicsEngine.

*/

UI::UI(GraphicsEngine* graph)
{
    ge = graph;
    mouseDown = false;

    ToolPanel *panel = new ToolPanel(ge, 10, 10);

    panel->addButton(tool = new ToolDraw(), true);
    panel->addButton(new ToolLine());
    panel->addButton(new ToolBox());
    panel->addButton(new ToolEllipse());
    panel->addButton(new ToolFill());
    panel->addButton(new ToolBezier());

    ge->addUIElement(panel);
    addListener(panel);

    colorpicker = new ColorPicker(ge);
    ge->addUIElement(colorpicker);
    addListener(colorpicker);

    thickness = new ThicknessSlider(graph);
    ge->addUIElement(thickness);
    addListener(thickness);

    option = new OptionButton(this);
    ge->addUIElement(option);
    addListener(option);

    //std::vector<Button*> tests = {new Button({100, 160}, 10), new Button({120, 160}, 20), new Button({160, 160}, 40), new Button({240, 160}, 80)};
    //for (Button *b : tests)
    //{
    //    ge->addObject(b);
    //    addListener(b);
    //}
}

/**
\brief Destructor

No implementation needed at this point.

*/

UI::~UI() {}

glm::ivec2 UI::prevMousePos() const
{
    return LastPosition;
}

bool UI::isMouseDown() const
{
    return mouseDown;
}

GraphicsEngine* UI::getEngine() const
{
    return ge;
}

glm::vec4 UI::getSelectedColor() const
{
    return colorpicker->getColor();
}

int UI::getThickness() const
{
    return thickness->getThickness();
}

bool UI::optionState() const
{
    return option->state();
}

const Tool* UI::getTool() const
{
    return tool;
}

void UI::addListener(Listener *l)
{
    listeners.push_back(l);
}

void UI::setToolActive(Tool *t)
{
    tool = t;
}

/**
\brief The method handles the SFML event processing and calls the keyboard state processor
method.

This method processes all events in the current SFML event queue and calls the
corresponding processing method.  At the end it calls the keyboard state processor
method, outside the event loop.

*/

void UI::processEvents()
{
    // Process user events
    sf::Event event;
    while (ge->pollEvent(event))
    {
        // Close Window or Escape Key Pressed: exit
        if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
            ge->close();

        // Key is pressed.
        if (event.type == sf::Event::KeyPressed)
            keyPressed(event.key);

        // Window is resized.
        if (event.type == sf::Event::Resized)
            ge->resize();

        if (event.type == sf::Event::MouseMoved)
            processMouseMoved(event.mouseMove);

        if (event.type == sf::Event::MouseButtonPressed)
            processMouseButtonPressed(event.mouseButton);

        if (event.type == sf::Event::MouseButtonReleased)
            processMouseButtonReleased(event.mouseButton);

        if (event.type == sf::Event::MouseWheelMoved)
            processMouseScrolled(event.mouseWheel);
    }

    // Process the state of the keyboard outside of event firing,
    keyboardStateProcessing();

}

/**
\brief The method updates the theta and psi values of the spherical camera
on a click and drag.  If the control key is down the vertical movement will
alter the radius of the camera.

\param mouseMoveEvent --- The SFML mouse move event structure.

*/

void UI::processMouseMoved(sf::Event::MouseMoveEvent mouseMoveEvent)
{
    ListenerContext<sf::Event::MouseMoveEvent> ctx = create_ctx(this, mouseMoveEvent);
    bool activated = false;
    for (Listener *l : listeners)
    {
        activated |= l->mouseMoved(ctx);
    }

    if (!activated) tool->mouseMoved(ctx);
}

/**
\brief On a left mouse click it will track the mouse down and tag the current position
of the mouse as the last position the mouse was at.

\param mouseButtonEvent --- The SFML mouse button event structure.

*/

void UI::processMouseButtonPressed(sf::Event::MouseButtonEvent mouseButtonEvent)
{
    ListenerContext<sf::Event::MouseButtonEvent> ctx = create_ctx(this, mouseButtonEvent);

    bool activated = false;
    for (Listener *l : listeners)
    {
        activated |= l->mousePressed(ctx);
    }

    if (!activated) tool->mousePressed(ctx);

    if (mouseButtonEvent.button == sf::Mouse::Left)
    {
        mouseDown = true;
        LastPosition.x = mouseButtonEvent.x;
        LastPosition.y = mouseButtonEvent.y;
    }
}

/**
\brief If the left mouse button is released this method will track the release and
exit any drag movement.

\param mouseButtonEvent --- The SFML mouse button event structure.

*/

void UI::processMouseButtonReleased(sf::Event::MouseButtonEvent mouseButtonEvent)
{
    ListenerContext<sf::Event::MouseButtonEvent> ctx = create_ctx(this, mouseButtonEvent);

    bool activated = false;
    for (Listener *l : listeners)
    {
        activated |= l->mouseReleased(ctx);
    }

    if (!activated) tool->mouseReleased(ctx);

    if (mouseButtonEvent.button == sf::Mouse::Left)
    {
        mouseDown = false;
    }
}

/**
\brief The function handles the keyboard input events from the user.

\param keyevent --- The SFML key code for the key pressed.

\remark

- Number keys: Selects the material
- Model Selection:
    - Z - Teapot
    - X - Sphere
    - C - Torus
    - V - Trefoil
    - B - Umbilic Torus
    - N - Braided Torus
    - M - Helical Torus
    - L - Mobius Strip
    - K - Tessellated Wall - 1x1
    - J - Tessellated Wall - 20x20

- R: Resets the window size to 700 X 500.
- A: Resets the window size to 600 X 600.
- F7: Activates the basic shader.
- F8: Activates the halfway shader.
- F9: Saves a screen shot of the graphics window to a png file.
- F10: Saves a screen shot of the graphics window to a jpeg file.
- F11: Turns on the spherical camera.
- F12: Turns on the yaw-pitch-roll camera.

*/

void UI::keyPressed(sf::Event::KeyEvent keyevent)
{
    switch(keyevent.code)
    {
    case sf::Keyboard::F9:
        ge->screenshotPNG();
        break;

    case sf::Keyboard::F10:
        ge->screenshotJPG();
        break;

    case sf::Keyboard::Z:
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
            ge->undo();
        break;

    case sf::Keyboard::Y:
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
            ge->redo();
        break;

    default:
        break;
    }
}

/**
\brief Calls the respective method for key processing depending on
which camera, spherical or yaw-pitch-roll, is currently selected.

*/

void UI::keyboardStateProcessing()
{
    if (ge->hasFocus())
    {

    }
}


bool UI::down(sf::Keyboard::Key key)
{
    return sf::Keyboard::isKeyPressed(key);
}

bool UI::anyDown(std::initializer_list<sf::Keyboard::Key> keys)
{
    for (sf::Keyboard::Key k : keys)
    {
        if (down(k))
        {
            return true;
        }
    }
    return false;
}

/** \brief Handles mouse scrolling, and zooms the camera accordingly */
void UI::processMouseScrolled(sf::Event::MouseWheelEvent event)
{

}
