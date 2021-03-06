#include "UI.h"

/**
\file UI.cpp
\brief User interface processor for the program.

\author    
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
    bool ctrldown = sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl);

    if (ge->isSphericalCameraOn() && mouseDown)
    {
        if (ctrldown)
        {
            ge->getSphericalCamera()->addR((LastPosition.y - mouseMoveEvent.y)*0.25);
        }
        else
        {
            ge->getSphericalCamera()->addTheta((mouseMoveEvent.x - LastPosition.x)*degf*10);
            ge->getSphericalCamera()->addPsi((mouseMoveEvent.y - LastPosition.y)*degf*10);
        }

        LastPosition.x = mouseMoveEvent.x;
        LastPosition.y = mouseMoveEvent.y;
    }
}

/**
\brief On a left mouse click it will track the mouse down and tag the current position
of the mouse as the last position the mouse was at.

\param mouseButtonEvent --- The SFML mouse button event structure.

*/

void UI::processMouseButtonPressed(sf::Event::MouseButtonEvent mouseButtonEvent)
{
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
    int key = keyevent.code;

    if (key >= sf::Keyboard::Num0 && key <= sf::Keyboard::Num9)
    {
        ge->activateMaterial(key);
        return;
    }

    switch (key)
    {

    case sf::Keyboard::F7:
        ge->useBasicShader();
        break;

    case sf::Keyboard::F8:
        ge->useHalfwayShader();
        break;

    case sf::Keyboard::F9:
        ge->screenshotPNG();
        break;

    case sf::Keyboard::F10:
        ge->screenshotJPG();
        break;

    case sf::Keyboard::F11:
        ge->setSphericalCameraOn();
        break;

    case sf::Keyboard::F12:
        ge->setYPRCameraOn();
        break;

    case sf::Keyboard::R:
        ge->setSize(700, 500);
        break;

    case sf::Keyboard::A:
        ge->setSize(600, 600);
        break;

    default:
        ge->activateModel(key);
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
        if (ge->isSphericalCameraOn())
            keyboardStateProcessingSphericalCamera();
        else
            keyboardStateProcessingYPRCamera();

        keyboardStateProcessingLight();
    }
}

/**
\brief The method processes the keyboard state if the spherical camera is the one currently
being used.

\remark

If no modifier keys are pressed:

- Left: Increases the camera's theta value.
- Right: Decreases the camera's theta value.
- Up: Increases the camera's psi value.
- Down: Decreases the camera's psi value.

If the control key is down:

- Up: Decreases the camera's radius.
- Down: Increases the camera's radius.

*/

void UI::keyboardStateProcessingSphericalCamera()
{
    bool ctrldown = anyDown({sf::Keyboard::LControl, sf::Keyboard::RControl});
    bool altdown = anyDown({sf::Keyboard::LAlt, sf::Keyboard::RAlt});
    bool someFKeyDown = anyDown({sf::Keyboard::F1, sf::Keyboard::F2, sf::Keyboard::F3, sf::Keyboard::F4});

    glm::ivec3 rot;
    glm::ivec3 trans;

    if (down(sf::Keyboard::F1))
    {
        updateState(rot.y, rot.x);
    }
    else if (down(sf::Keyboard::F2))
    {
        updateState(rot.y, rot.z);
    }
    else if (down(sf::Keyboard::F3))
    {
        updateState(trans.x, trans.z);
    }
    else if (down(sf::Keyboard::F4))
    {
        int dummy = 0;
        updateState(trans.y, dummy);
    }

    ge->rotate(rot);
    ge->translate(trans);

    if (someFKeyDown || altdown)
        return;

    if (ctrldown)
    {
        if (down(sf::Keyboard::Up))
            ge->getSphericalCamera()->addR(-0.1);

        if (down(sf::Keyboard::Down))
            ge->getSphericalCamera()->addR(0.1);
    }
    else
    {
        if (down(sf::Keyboard::Left))
            ge->getSphericalCamera()->addTheta(1);

        if (down(sf::Keyboard::Right))
            ge->getSphericalCamera()->addTheta(-1);

        if (down(sf::Keyboard::Up))
            ge->getSphericalCamera()->addPsi(1);

        if (down(sf::Keyboard::Down))
            ge->getSphericalCamera()->addPsi(-1);
    }
}


void UI::keyboardStateProcessingLight()
{
    bool ctrldown = anyDown({sf::Keyboard::LControl, sf::Keyboard::RControl});
    bool altdown = anyDown({sf::Keyboard::LAlt, sf::Keyboard::RAlt});
    bool someFKeyDown = anyDown({sf::Keyboard::F1, sf::Keyboard::F2, sf::Keyboard::F3, sf::Keyboard::F4});

    if (!someFKeyDown && altdown)
    {
        if (ctrldown)
        {
            if (down(sf::Keyboard::Up))
                ge->getLtPos()->addR(-0.1);

            if (down(sf::Keyboard::Down))
                ge->getLtPos()->addR(0.1);
        }
        else
        {
            if (down(sf::Keyboard::Left))
                ge->getLtPos()->addTheta(1);

            if (down(sf::Keyboard::Right))
                ge->getLtPos()->addTheta(-1);

            if (down(sf::Keyboard::Up))
                ge->getLtPos()->addPsi(1);

            if (down(sf::Keyboard::Down))
                ge->getLtPos()->addPsi(-1);
        }
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

void UI::updateState(int& n1, int& n2)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) n1 -= 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) n1 += 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) n2 += 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) n2 -= 1;
}

/**
\brief The method processes the keyboard state if the yaw-pitch-roll camera is the
one currently being used.

\remark

If no modifier keys are pressed:

- Left: Increases the yaw.
- Right: Decreases the yaw.
- Up: Increases the pitch.
- Down: Decreases the pitch.

If the control key is down:

- Left: Increases the roll.
- Right: Decreases the roll.
- Up: Moves the camera forward.
- Down: Moves the camera backward.

If the shift key is down:

- Left: Moves the camera left.
- Right: Moves the camera right.
- Up: Moves the camera up.
- Down: Moves the camera down.

*/

void UI::keyboardStateProcessingYPRCamera()
{
    bool ctrldown = sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl);
    bool shiftdown = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift);
    bool altdown = sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt) || sf::Keyboard::isKeyPressed(sf::Keyboard::RAlt);

    if (altdown)
        return;

    if (shiftdown)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            ge->getYPRCamera()->moveRight(-0.1);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            ge->getYPRCamera()->moveRight(0.1);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            ge->getYPRCamera()->moveUp(0.1);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            ge->getYPRCamera()->moveUp(-0.1);
    }
    else if (ctrldown)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            ge->getYPRCamera()->addRoll(1);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            ge->getYPRCamera()->addRoll(-1);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            ge->getYPRCamera()->moveForward(0.1);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            ge->getYPRCamera()->moveForward(-0.1);
    }
    else
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            ge->getYPRCamera()->addYaw(1);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            ge->getYPRCamera()->addYaw(-1);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            ge->getYPRCamera()->addPitch(1);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            ge->getYPRCamera()->addPitch(-1);
    }
}

/** \brief Handles mouse scrolling, and zooms the camera accordingly */
void UI::processMouseScrolled(sf::Event::MouseWheelEvent event)
{
    if (ge->isSphericalCameraOn())
    {
        ge->getSphericalCamera()->addR(-event.delta);
    }
    else {
        ge->getYPRCamera()->moveForward(-event.delta);
    }
}
