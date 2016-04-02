#include "UI.h"

/**
\file UI.cpp
\brief User interface processor for the program.

\author    Don Spickler
\version   1.1
\date      Written: 1/16/2016  <BR> Revised: 1/16/2016

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
    srand(clock());
}


/**
\brief Destructor

No implementation needed at this point.

*/

UI::~UI() {}

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

    }

    // Process the state of the keyboard outside of event firing,
    keyboardStateProcessing();

}

/**
\brief Method that takes in the integer mouse position coordinates from a mouse event
and converts them into screen coordinates.

It is assumed that the array screenBounds holds the bounds to the screen in the form
(l, r, b, t).

\param mousePosition --- A sf::Vector2i holding the x and y positions taken from the
mouse position coordinates of a mouse event.

\return A lib::Point2D holding the screen (x, y) position of the mouse.

*/

lib::Point2D UI::MouseToScreenConversion(sf::Vector2i mousePosition)
{
    lib::Point2D sc;
    float* screenBounds = ge->getScreenBounds();

    sc.x = (float)mousePosition.x / ge->getSize().x * (screenBounds[1] - screenBounds[0]) + screenBounds[0];
    sc.y = screenBounds[3] - (float)mousePosition.y / ge->getSize().y * (screenBounds[3] - screenBounds[2]);

    return sc;
}

/**
\brief The method outputs the position of the mouse on a move event and if the system is
in a click and drag mode it will resize the box about the center with the cursor being
on the green vertex.

\param mouseMoveEvent --- The SFML mouse move event structure.

*/

void UI::processMouseMoved(sf::Event::MouseMoveEvent mouseMoveEvent)
{
    lib::Point2D sc = MouseToScreenConversion(sf::Vector2i(mouseMoveEvent.x, mouseMoveEvent.y));

    // Update all hover states
    ge->forEachBox([sc](Box* b) {b->setHover(b->contains(sc));});

    if (mouseDown)
    {
        // If we are dragging some boxes, update their positions
        for (DraggingBox db : capturedBoxes)
        {
            db.box->setCenter({db.origCenter.x + (sc.x - pressPos.x), db.origCenter.y + (sc.y - pressPos.y)});
        }
    }
}

/**
\brief The method outputs the position and the button pressed of the mouse on a button event.

It also updates the box by centering it on the cursor if the click was a left click and
adjusting the size of the box on a right click.  On the right click the box will be adjusted
so that the green corner of the box will be on the cursor.

\param mouseButtonEvent --- The SFML mouse button event structure.

*/

void UI::processMouseButtonPressed(sf::Event::MouseButtonEvent mouseButtonEvent)
{
    lib::Point2D sc = MouseToScreenConversion(sf::Vector2i(mouseButtonEvent.x, mouseButtonEvent.y));

    bool ctrl = sf::Keyboard::isKeyPressed(sf::Keyboard::RControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::LControl);
    if (mouseButtonEvent.button == sf::Mouse::Left)
    {
        if (!mouseDown)
        {
            // Update the dragging state and capture any boxes currently under the cursor, as well as the current position of the cursor
            mouseDown = true;
            pressPos = sc;
            ge->forEachBox([this, sc](Box* b) {if (b->contains(sc)) capturedBoxes.push_back({b, b->getCenter()});});
        }
    }
    else if (mouseButtonEvent.button == sf::Mouse::Right)
    {
        if (ctrl)
        {
            // Ctrl is pressed, so remove any boxes under the cursor
            std::vector<Box*> toRemove;
            ge->forEachBox([sc, &toRemove](Box* b){if (b->contains(sc)) toRemove.push_back(b);});
            for (Box* b : toRemove)
            {
                ge->removeBox(b);
            }
        }
        else
        {
            // Ctrl is not pressed, so create a new random box at the cursor position
            float w = (lib::rand_float() * 0.15f) + 0.1f;
            float h = (lib::rand_float() * 0.15f) + 0.1f;

            Box *box = new Box(sc, w, h);
            box->setColor({lib::rand_float(), lib::rand_float(), lib::rand_float()});

            ge->addBox(box);
        }
    }
}

/**
\brief The method simply outputs the position and the button released of the mouse
on a button event.

\param mouseButtonEvent --- The SFML mouse button event structure.

*/

void UI::processMouseButtonReleased(sf::Event::MouseButtonEvent mouseButtonEvent)
{
    lib::Point2D sc = MouseToScreenConversion(sf::Vector2i(mouseButtonEvent.x, mouseButtonEvent.y));

    if (mouseButtonEvent.button == sf::Mouse::Left && mouseDown)
    {
        // Reset the dragging state and uncapture all boxes
        mouseDown = false;
        pressPos = {0, 0};
        capturedBoxes.clear();
    }
}

/**
\brief The function handles the keyboard input events from the user.

\param keyevent --- The SFML key code for the key pressed.

\remark

If no modifier keys are pressed:

- F9: Saves a screen shot of the graphics window to a png file.

- F10: Saves a screen shot of the graphics window to a jpeg file.

- M: Toggles between fill mode and line mode to draw the triangles.

- R: Resets the window size to 700 X 500.

- A: Resets the window size to 600 X 600.

- C: Clears the boxes from the screen.

- P: Toggles secret mode.
*/

void UI::keyPressed(sf::Event::KeyEvent keyevent)
{
    int key = keyevent.code;

    switch (key)
    {
    // F9 takes a screenshot.
    case sf::Keyboard::F9:
        ge->screenshotPNG();
        break;

    // F10 takes a screenshot.
    case sf::Keyboard::F10:
        ge->screenshotJPG();
        break;

    // If the M key is pressed toggle the display mode between Fill and Line.
    case sf::Keyboard::M:
        ge->changeMode();
        break;

    // Resets the screen size to 700 X 500.
    case sf::Keyboard::R:
        ge->setSize(700, 500);
        break;

    // Sets the screen size to 600 X 600.
    case sf::Keyboard::A:
        ge->setSize(600, 600);
        break;

    // Clears all boxes
    case sf::Keyboard::C:
        ge->clear();
        break;

    // Toggles secret mode
    case sf::Keyboard::P:
        secret_mode = !secret_mode;
        break;

    default:
        break;
    }
}

/**
\brief The method processes the keyboard state.
*/

void UI::keyboardStateProcessing()
{
    // The amount to move when a key is pressed
    const float move = secret_mode ? 0.25f : 0.005f;
    // Only used for secret mode
    const float change = secret_mode ? (0.1f / Box::index_tracker) : 1;
    Point2D delta = {0, 0};
    // Check all direction keys and modify the delta to match
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        delta.x -= move;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        delta.x += move;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        delta.y += move;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        delta.y -= move;
    }

    // Apply the delta to the box, doing special math for secret mode
    ge->forEachBox([this, delta, change](Box *b)
    {
        float x = secret_mode ? b->getCenter().x + (delta.x * (b->index * change)) : b->getCenter().x + delta.x;
        float y = secret_mode ? b->getCenter().y + (delta.y * (b->index * change)) : b->getCenter().y + delta.y;

        b->setCenter({x, y});
    });
}
