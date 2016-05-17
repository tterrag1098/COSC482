#include "GraphicsEngine.h"
#include "LineSeg.h"
#include "Body.h"
#include "GhostPlanet.h"

/**
\file GraphicsEngine.cpp
\brief Main graphics driver for the program.

This class extends sf::RenderWindow.

\author    Don Spickler
\version   1.2
\date      Written: 4/5/2016  <BR> Revised: 4/10/2016

*/

GLuint GraphicsEngine::ModelLoc = 0;
GLuint GraphicsEngine::NormalLoc = 0;
GLuint GraphicsEngine::PVMLoc = 0;
GLuint GraphicsEngine::texTransLoc = 0;

/**
\brief Constructor

\param title --- Title to be placed in the titlebar of the graphics window.

\param width --- The width (in pixels) of the graphics window.

\param height --- The height (in pixels) of the graphics window.

Creates rendering window, loads the shaders, and sets some initial data settings.

*/

GraphicsEngine::GraphicsEngine(std::string title, GLint width, GLint height) :
    sf::RenderWindow(sf::VideoMode(width, height),
                     title,
                     sf::Style::Default,
                     sf::ContextSettings(24, 8, 4, 3, 3)),

    fboShader(Shader("World.vert", "World.frag")),
    screenShader(Shader("PostProcessing.vert", "PostProcessing.frag")),
    cmShader(Shader("CubeMap.vert", "CubeMap.frag")),
    uiShader(Shader("Passthrough.vert", "Passthrough.frag"))
{
    uiShader.use();
    uiProjLoc = glGetUniformLocation(uiShader.program, "Projection");

    screenShader.use();

    glGenFramebuffers(1, &worldFbo);
    glGenTextures(1, &fboTex);
    glGenRenderbuffers(1, &rbo);

    glBindFramebuffer(GL_FRAMEBUFFER, worldFbo);
    glBindTexture(GL_TEXTURE_2D, fboTex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fboTex, 0);

    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, getSize().x, getSize().y);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glUniform1i(glGetUniformLocation(screenShader.program, "screenTex"), 0);

    glGenVertexArrays(1, &screenVao);
    GLuint buffer;
    glGenBuffers(1, &buffer);

    glBindVertexArray(screenVao);

    sf::Vector2u scr = getSize();
    glm::vec2 verts[6] = {{-1, -1}, {1, -1}, {-1, 1}, {-1, 1}, {1, -1}, {1, 1}};
    glm::vec2 uvs[6] = {{0, 0}, {1, 0}, {0, 1}, {0, 1}, {1, 0}, {1, 1}};

    int size = sizeof(glm::vec2) * 6;

    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, size * 2, NULL, GL_STATIC_DRAW);

    glBufferSubData(GL_ARRAY_BUFFER, 0, size, verts);
    glBufferSubData(GL_ARRAY_BUFFER, size, size, uvs);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(size));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    pe = new PhysicsEngine();

    STAR->mat = Material(loadTexture("assets/sun.jpg", fboShader), loadTexture("assets/sun_spec.jpg", fboShader), 0.75f, 0.75f, 0.75f, 1, 0.2f);
    EARTH->mat = Material(loadTexture("assets/earth.jpg", fboShader), loadTexture("assets/earth_spec.jpg", fboShader), 0, 0, 0, 0, 20);
    MOON->mat = Material(loadTexture("assets/moon.jpg", fboShader), loadTexture("assets/moon_spec.jpg", fboShader), 0, 0, 0, 0, 10);

    BARREN1->mat = Material(loadTexture("assets/barren1.jpg", fboShader), loadTexture("assets/barren1_spec.jpg", fboShader), 0, 0, 0, 0, 10);
    BARREN2->mat = Material(loadTexture("assets/barren2.jpg", fboShader), loadTexture("assets/barren2_spec.jpg", fboShader), 0, 0, 0, 0, 20);
    BARREN3->mat = Material(loadTexture("assets/barren3.jpg", fboShader), loadTexture("assets/barren3_spec.jpg", fboShader), 0, 0, 0, 0, 10);

    ALIEN1->mat = Material(loadTexture("assets/alien1.jpg", fboShader), loadTexture("assets/alien1_spec.jpg", fboShader), 0, 0, 0, 0, 20);
    ALIEN2->mat = Material(loadTexture("assets/alien2.jpg", fboShader), loadTexture("assets/alien2_spec.jpg", fboShader), 0, 0, 0, 0, 30);

    ghost = new GhostPlanet();

    BodySphere *star = new BodySphere("Sun", STAR, {0, 0, 0}, 3, 1e13);
    addBody(star);
    pe->addBody(star);
    selected = star;

    BodySphere *earth1 = new BodySphere("Earth", EARTH, {-10, 0, -5}, 0.3, 1e10);
    earth1->setVelocity({0, 0.5, 7});
    addBody(earth1);
    pe->addBody(earth1);

    BodySphere *earth2 = new BodySphere("Barren1", BARREN1, {6, 0, -8}, 0.3, 1e10);
    earth2->setVelocity({-8, -0.8, 0});
    addBody(earth2);
    pe->addBody(earth2);

    BodySphere *earth3 = new BodySphere("Barren2", BARREN2, {12, 0, 4}, 0.3, 1e10);
    earth3->setVelocity({0, 0.5, -6});
    addBody(earth3);
    pe->addBody(earth3);

    BodySphere *earth4 = new BodySphere("Barren3", BARREN3, {0, 0, 15}, 0.3, 1e10);
    earth4->setVelocity({7, -0.5, 0});
    addBody(earth4);
    pe->addBody(earth4);

    BodySphere *moon = new BodySphere("Alien1", ALIEN1, {-15, 0, 0}, 0.3, 1e10);
    moon->setVelocity({0, -1, 8});
    addBody(moon);
    pe->addBody(moon);

    BodySphere *moon2 = new BodySphere("Alien2", ALIEN2, {15, 0, 0}, 0.3, 1e10);
    moon2->setVelocity({0, 1, -8});
    addBody(moon2);
    pe->addBody(moon2);

    if (!fboShader.program)
    {
        std::cerr << "Could not load Shader programs." << std::endl;
        exit(EXIT_FAILURE);
    }

    if (!cmShader.program)
    {
        std::cerr << "Could not load Cube Map Shader programs." << std::endl;
        exit(EXIT_FAILURE);
    }

    // Turn on the shader & get location of transformation matrix.
    fboShader.use();
    PVMLoc = glGetUniformLocation(fboShader.program, "PVM");
    ModelLoc = glGetUniformLocation(fboShader.program, "Model");
    NormalLoc = glGetUniformLocation(fboShader.program, "NormalMatrix");
    texTransLoc = glGetUniformLocation(fboShader.program, "textrans");

    // Initialize some data.
    mode = GL_FILL;
    sscount = 1;
    CameraNumber = 1;

    // Set position of spherical camera
    sphcamera.setPosition(40, 0, 90);

    glEnable(GL_MULTISAMPLE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    setFramerateLimit(240);
    setVerticalSyncEnabled(false);

    glm::vec4 GlobalAmbient(0.05f, 0.05f, 0.05f, 1);
    glUniform4fv(glGetUniformLocation(fboShader.program, "GlobalAmbient"), 1, glm::value_ptr(GlobalAmbient));

    CMSphere.createSphereOBJ(100000, 40, 40);
    CMSphere.load(0, 1, 2, 3);

    model = glm::mat4(1.0);

    // Load model matrix.
    glUniformMatrix4fv(ModelLoc, 1, GL_FALSE, glm::value_ptr(model));

    // Extract upper left 3 X 3 from model matrix.
    glm::mat3 nM(model);

    // Create the Normal Transformation matrix N = (M^(-1))^T, where M is the
    // upper left 3 X 3 from model matrix.
    glm::mat3 normalMatrix = glm::transpose(glm::inverse(nM));
    glUniformMatrix3fv(NormalLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));

//  Texture transformation matrix experiments
    textrans = glm::mat4(1.0);
//    textrans = glm::rotate(textrans, 45*degf, glm::vec3(0, 0, 1));
//    textrans = glm::translate(textrans, glm::vec3(0.5, 0.25, 0));
//    textrans = glm::scale(textrans, glm::vec3(2, 2, 1));

    sf::Image texture;
    std::string filename;

    glGenTextures(6, texID);
    filename = "assets/earth.jpg";

    if (!texture.loadFromFile(filename))
        std::cerr << "Could not load texture: " << filename << std::endl;

    //  Link the texture to the shader.
    GLuint tex1_uniform_loc = glGetUniformLocation(fboShader.program, "tex");
    glUniform1i(tex1_uniform_loc, 0);

    //  Load the texture into texture memory.
    glBindTexture(GL_TEXTURE_2D, texID[0]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture.getSize().x, texture.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture.getPixelsPtr());
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    cmShader.use();

    glBindFramebuffer(GL_FRAMEBUFFER, worldFbo);


    //  Load in Cube Map
    glUniform1i(glGetUniformLocation(cmShader.program, "cmtex"), 0);

    // Generate a new cube map texture and bind to it
    glGenTextures (1, &CubeMapTexId);
    glBindTexture (GL_TEXTURE_CUBE_MAP, CubeMapTexId);

    // Setup some parameters for texture filters and mipmapping
    glTexParameteri (GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri (GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri (GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri (GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri (GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    texture.loadFromFile("assets/skybox_left.png");
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGBA, texture.getSize().x, texture.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture.getPixelsPtr());
    texture.loadFromFile("assets/skybox_right.png");
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGBA, texture.getSize().x, texture.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture.getPixelsPtr());
    texture.loadFromFile("assets/skybox_up.png");
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGBA, texture.getSize().x, texture.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture.getPixelsPtr());
    texture.loadFromFile("assets/skybox_down.png");
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGBA, texture.getSize().x, texture.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture.getPixelsPtr());
    texture.loadFromFile("assets/skybox_front.png");
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGBA, texture.getSize().x, texture.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture.getPixelsPtr());
    texture.loadFromFile("assets/skybox_back.png");
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGBA, texture.getSize().x, texture.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture.getPixelsPtr());

    glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

    printOpenGLErrors();

    // Make it the active window for OpenGL calls, resize to set projection matrix.
    setActive();
    resize();
}


/**
\brief Destructor

Currently empty, no allocated memory to clear.

*/

GraphicsEngine::~GraphicsEngine() {}

GLuint GraphicsEngine::loadTexture(std::string path, Shader activeShader)
{
    sf::Image texture;
    bool texloaded = texture.loadFromFile(path);

    if (!texloaded)
    {
        std::cerr << "Could not load texture." << std::endl;
        exit(EXIT_FAILURE);
    }

    GLuint texID;
    glGenTextures(1, &texID);
    glUniform1i(glGetUniformLocation(activeShader.program, "tex"), 1);

    //  Load the texture into texture memory.
    glBindTexture(GL_TEXTURE_2D, texID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture.getSize().x, texture.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture.getPixelsPtr());
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return texID;
}

GLuint GraphicsEngine::loadMaterial(std::string path)
{

}

void GraphicsEngine::activateTexture(int texId, Shader activeShader)
{
    if (texId >= 0)
    {
        glActiveTexture(GL_TEXTURE0+1);
        glUniform1i(glGetUniformLocation(activeShader.program, "useTexture"), 1);
        glBindTexture(GL_TEXTURE_2D, texId);
    }
    else
    {
        glUniform1i(glGetUniformLocation(activeShader.program, "useTexture"), 0);
    }
}

void GraphicsEngine::addBody(BodyDrawable *obj)
{
    obj->load();
    bodies.push_back(obj);

    fboShader.use();

    if (obj->getMaterial().getEmission().xyz() != glm::vec3(0, 0, 0))
    {
        glm::vec4 e = obj->getMaterial().getEmission();
        Light lt;
        lt.setLight(true,
                glm::vec4(0.0, 0.0, 0.0, 1.0),
                glm::vec3(-1.0, -1.0, -1.0),
                glm::vec4(0.05, 0.05, 0.05, 1.0),
                e*0.75f,
                e,
                180.0, 0.0,
                glm::vec3(1.0, 0.0, 0.0)
            );
        obj->assignLight(nextLight);
        LoadLight(lt, "Lt", nextLight++);
        glUniform1i(glGetUniformLocation(fboShader.program, "numLights"), nextLight);
    }
}

void GraphicsEngine::removeBody(const BodyDrawable *obj)
{
    bodies.erase(std::find(bodies.begin(), bodies.end(), obj));
    if (obj->getLight() >= 0)
    {
        turnLightOff("Lt", obj->getLight());
    }
}

void GraphicsEngine::addObject(Drawable *obj)
{
    objects.push_back(obj);
    obj->load();
}

void GraphicsEngine::addUIElement(Drawable *obj)
{
    ui.push_back(obj);
    obj->load();
}

BodyDrawable* GraphicsEngine::getSelectedBody() const
{
    return selected;
}

std::vector<BodyDrawable*> GraphicsEngine::getBodies() const
{
    return bodies;
}

PhysicsEngine* GraphicsEngine::getPhysics() const
{
    return pe;
}

GhostPlanet* GraphicsEngine::getGhost() const
{
    return ghost;
}

/**
\brief The function responsible for drawing to the OpenGL frame buffer.

This function clears the screen and calls the draw functions of the box and circle.

*/

void GraphicsEngine::display()
{
    pe->updateObjects();

    sphcamera.setCenter(selected ? selected->getPosF() : glm::vec3(0));
    sphcamera.setR(std::min(10000.0f, sphcamera.getR()));
    if (selected)
    {
        sphcamera.setR(std::max(selected->getRadius() * 2, sphcamera.getR()));
    }

    glActiveTexture(GL_TEXTURE0);

    // First pass
    glBindFramebuffer(GL_FRAMEBUFFER, worldFbo);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // We're not using stencil buffer now
    glEnable(GL_DEPTH_TEST);

    // Set view matrix via current camera.
    if (CameraNumber == 1)
        view = sphcamera.lookAt();
    else if (CameraNumber == 2)
        view = yprcamera.lookAt();

    glm::mat4 pvm = projection * view * model;

    cmShader.use();
    glUniformMatrix4fv(glGetUniformLocation(cmShader.program, "PVM"), 1, GL_FALSE, glm::value_ptr(pvm));

    CMSphere.draw(this);

    fboShader.use();

    glm::vec3 eye;
    if (CameraNumber == 1)
        eye = sphcamera.getPosition();
    else if (CameraNumber == 2)
        eye = yprcamera.getPosition();

    glUniform3fv(glGetUniformLocation(fboShader.program, "eye"), 1, glm::value_ptr(eye));

    glUniformMatrix4fv(texTransLoc, 1, GL_FALSE, glm::value_ptr(textrans));

    // Lighting pass
    for (BodyDrawable *obj : bodies)
    {
        if (obj->getLight() >= 0)
        {
            char name[20];
            snprintf(name, 20, "Lt[%d].position", obj->getLight());
            glm::vec3 pos = glm::vec3(obj->getPos());
            glUniform4fv(glGetUniformLocation(fboShader.program, name), 1, glm::value_ptr(pos));
        }
    }

    // Drawing pass
    for (BodyDrawable* obj : bodies)
    {
        loadMaterial(obj->getMaterial());
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, obj->getMaterial().getDiffuse());
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, obj->getMaterial().getSpecular());

        obj->draw(this);
    }

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
    loadMaterial(ghost->getMaterial());
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, ghost->getMaterial().getDiffuse());
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, ghost->getMaterial().getSpecular());
    ghost->draw(this);
    glFrontFace(GL_CCW);
    glDisable(GL_CULL_FACE);

    for (Drawable *d : objects)
    {
        d->draw(this);
    }

    glUniformMatrix4fv(PVMLoc, 1, GL_FALSE, glm::value_ptr(projection*view*model));
    glUniformMatrix4fv(ModelLoc, 1, GL_FALSE, glm::value_ptr(model));

    screenShader.use();

    // Second pass
    glBindFramebuffer(GL_FRAMEBUFFER, 0); // back to default
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    screenShader.use();
    glBindVertexArray(screenVao);
    glDisable(GL_DEPTH_TEST);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, fboTex);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);

    uiShader.use();
    for (Drawable *d : ui)
    {
        d->draw(this);
    }

    printOpenGLErrors();
    sf::RenderWindow::display();
}

void GraphicsEngine::updateModelMat(glm::mat4 mat)
{
    if (glGetIntegerv(GL_CURRENT_PROGRAM, &tempHolder), tempHolder != fboShader.program) return;

    glUniformMatrix4fv(ModelLoc, 1, GL_FALSE, glm::value_ptr(mat));
    glUniformMatrix4fv(PVMLoc, 1, GL_FALSE, glm::value_ptr(projection * view * model * mat));

    glm::mat3 nM(mat);
    nM = glm::transpose(glm::inverse(nM));
    glUniformMatrix3fv(NormalLoc, 1, GL_FALSE, glm::value_ptr(nM));
}

void GraphicsEngine::setUseLighting(bool use)
{
    if (glGetIntegerv(GL_CURRENT_PROGRAM, &tempHolder), tempHolder != fboShader.program) return;
    glUniform1i(glGetUniformLocation(fboShader.program, "useLighting"), use);
}

void GraphicsEngine::setFullbright(bool fb)
{
    if (glGetIntegerv(GL_CURRENT_PROGRAM, &tempHolder), tempHolder != fboShader.program) return;
    glUniform1i(glGetUniformLocation(fboShader.program, "fullbright"), fb);
}

void GraphicsEngine::rayCastSelect(float mx, float my)
{
    glm::vec2 nds;

    nds.x = (((float) mx / getSize().x) * 2) - 1;
    nds.y = 1 - (((float) my / getSize().y) * 2);

    glm::vec4 dir(nds, 1, 1);

    dir = glm::inverse(projection) * dir;
    dir = glm::normalize(glm::inverse(view) * dir);

    std::vector<BodyDrawable*> intersections;

    glm::vec3 o = sphcamera.getPosition();
    glm::vec3 l = dir.xyz();

#ifdef RAYTRACE_DEBUG
    LineSeg *line = new LineSeg(o, o + (l * 100.0f));
    line->load();
    objects.push_back(line);
#endif // RAYTRACE_DEBUG

    for (BodyDrawable *b : bodies)
    {
        glm::vec3 c(b->getPos());

        float r = b->getRadius();

        float res = glm::dot(l, o - c);
        res *= res;

        float mag = glm::length(o - c);
        mag *= mag;
        float r2 = r * r;

        res = res - mag + r2;

        if (res >= 0)
        {
            intersections.push_back(b);
        }
    }

    float minDist = INT_MAX;
    selected = NULL;
    for (BodyDrawable *b : intersections)
    {
        float dist = glm::distance(o, glm::vec3(b->getPos()));
        if (dist < minDist)
        {
            selected = b;
            minDist = dist;
        }
    }
}

void GraphicsEngine::setSelected(BodyDrawable *obj)
{
    selected = obj;
}

/**
\brief Changes the fill and line mode being used.

*/

void GraphicsEngine::changeMode()
{
    if (mode == GL_FILL)
        mode = GL_LINE;
    else
        mode = GL_FILL;

    glPolygonMode(GL_FRONT_AND_BACK, mode);
}

/**
\brief Saves a screenshot of the current display to a file, ScreenShot###.ext.

\param ext --- String holding the extension of the filename, and hence the image
data type.  The extension can be any extension of an SFML supported data type for
the saveToFile method of the sf;:Image class.

*/

void GraphicsEngine::screenshot(std::string ext)
{
    char ssfilename[100];
    sprintf(ssfilename, "ScreenShot%d.%s", sscount, ext.c_str());
    sf::Image img = capture();
    img.saveToFile(ssfilename);
    sscount++;
}

/**
\brief Saves a screenshot of the current display to a file, ScreenShot###.jpg.

*/

void GraphicsEngine::screenshotJPG()
{
    screenshot("jpg");
}

/**
\brief Saves a screenshot of the current display to a file, ScreenShot###.png.

*/

void GraphicsEngine::screenshotPNG()
{
    screenshot("png");
}

/**
\brief Handles the resizing events of the window.

Sets the viewport to the entire screen and recalculates the projection matrix.
*/

void GraphicsEngine::resize()
{
    float w = getSize().x;
    float h = getSize().y;

    glViewport(0, 0, getSize().x, getSize().y);
    projection = glm::perspective(50.0f*degf, w/h, 0.1f, 200000.0f);

    uiShader.use();
    glm::mat4 uiProj = glm::ortho(0.0f, w, h, 0.0f);
    glUniformMatrix4fv(uiProjLoc, 1, GL_FALSE, glm::value_ptr(uiProj));

    glBindFramebuffer(GL_FRAMEBUFFER, worldFbo);
    glBindTexture(GL_TEXTURE_2D, fboTex);

    screenShader.use();

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, getSize().x, getSize().y, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, getSize().x, getSize().y);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR: Framebuffer is not complete!" << std::endl;

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

/**
\brief Sets the size of the rendering window.

\param width --- the width in pixels of the new size.

\param height --- the height in pixels of the new size.

*/

void GraphicsEngine::setSize(unsigned int width, unsigned int height)
{
    sf::RenderWindow::setSize(sf::Vector2u(width, height));
}

/**
\brief Returns a pointer to the spherical camera.

*/

SphericalCamera* GraphicsEngine::getSphericalCamera()
{
    return &sphcamera;
}

/**
\brief Returns a pointer to the yaw-pitch-roll camera.

*/

YPRCamera* GraphicsEngine::getYPRCamera()
{
    return &yprcamera;
}

/**
\brief Prints all OpenGL errors to stderr.

*/

void GraphicsEngine::printOpenGLErrors()
{
    GLenum errCode;
    const GLubyte *errString;

    while ((errCode = glGetError()) != GL_NO_ERROR)
    {
        errString = gluErrorString(errCode);
        fprintf(stderr, "OpenGL Error: %s\n", errString);
    }
}

/**
\brief Prints the glm matrix to the console window.  Remember that glm
matrices are column major. This is for the 3 X 3 matrices.

\param m --- the glm matrix to be displayed.

*/

void GraphicsEngine::print_GLM_Matrix(glm::mat4 m)
{
    for (int r = 0; r < 4; r++)
    {
        for (int c = 0; c < 4; c++)
            printf("%7.2f", m[c][r]);

        std::cout << std::endl;
    }
    std::cout << std::endl;
}


/**
\brief Prints the glm matrix to the console window.  Remember that glm
matrices are column major. This is for the 3 X 3 matrices.

\param m --- the glm matrix to be displayed.

*/

void GraphicsEngine::print_GLM_Matrix(glm::mat3 m)
{
    for (int r = 0; r < 3; r++)
    {
        for (int c = 0; c < 3; c++)
            printf("%7.2f", m[c][r]);

        std::cout << std::endl;
    }
    std::cout << std::endl;
}

/**
\brief Returns true if the spherical camera is currently in use.

\return True if the spherical camera is currently in use and false otherwise.

*/

GLboolean GraphicsEngine::isSphericalCameraOn()
{
    return CameraNumber == 1;
}

/**
\brief Turns the spherical camera on.

*/

void GraphicsEngine::setSphericalCameraOn()
{
    CameraNumber = 1;
}

/**
\brief Returns true if the yaw-pitch-roll camera is currently in use.

\return True if the yaw-pitch-roll camera is currently in use and false otherwise.

*/

GLboolean GraphicsEngine::isYPRCameraOn()
{
    return CameraNumber == 2;
}

/**
\brief Turns the YPR camera on.

*/

void GraphicsEngine::setYPRCameraOn()
{
    CameraNumber = 2;
}

/**
\brief Turns the light on

*/

void GraphicsEngine::turnLightOn()
{
    fboShader.use();
    glUniform1i(glGetUniformLocation(fboShader.program, "Lt.on"), true);
}

/**
\brief Turns the light off

*/

void GraphicsEngine::turnLightOff()
{
    fboShader.use();
    glUniform1i(glGetUniformLocation(fboShader.program, "Lt.on"), false);
}

/**
\brief Loads the light structure to the shader light structure.

\param Lt --- Light structure to load.

*/

void GraphicsEngine::loadLight(Light Lt)
{
    fboShader.use();

    glUniform1i(glGetUniformLocation(fboShader.program, "Lt.on"), Lt.getOn());
    glUniform4fv(glGetUniformLocation(fboShader.program, "Lt.position"), 1, glm::value_ptr(Lt.getPosition()));
    glUniform4fv(glGetUniformLocation(fboShader.program, "Lt.ambient"), 1, glm::value_ptr(Lt.getAmbient()));
    glUniform4fv(glGetUniformLocation(fboShader.program, "Lt.diffuse"), 1, glm::value_ptr(Lt.getDiffuse()));
    glUniform4fv(glGetUniformLocation(fboShader.program, "Lt.specular"), 1, glm::value_ptr(Lt.getSpecular()));
    glUniform3fv(glGetUniformLocation(fboShader.program, "Lt.spotDirection"), 1, glm::value_ptr(Lt.getSpotDirection()));
    glUniform3fv(glGetUniformLocation(fboShader.program, "Lt.attenuation"), 1, glm::value_ptr(Lt.getAttenuation()));
    glUniform1f(glGetUniformLocation(fboShader.program, "Lt.spotCutoff"), Lt.getSpotCutoff());
    glUniform1f(glGetUniformLocation(fboShader.program, "Lt.spotExponent"), Lt.getSpotExponent());
}

/**
\brief Loads the material structure to the shader material structure.

\param Mat --- Material structure to load.

*/

void GraphicsEngine::loadMaterial(Material Mat)
{
    fboShader.use();

    glUniform1i(glGetUniformLocation(fboShader.program, "Mat.diffuse"), 1);
    glUniform1i(glGetUniformLocation(fboShader.program, "Mat.specular"), 2);
    glUniform4fv(glGetUniformLocation(fboShader.program, "Mat.emission"), 1, glm::value_ptr(Mat.getEmission()));
    glUniform1f(glGetUniformLocation(fboShader.program, "Mat.shininess"), Mat.getShininess());
}

/**
\brief Loads a single light into a light array in the shader.

\param Lt --- Light to load.

\param name --- The name of the array in the shader.

\param i --- The index of the light to load.

*/

void GraphicsEngine::LoadLight(Light Lt, std::string name, int i)
{
    fboShader.use();

    const char* arrayname = name.c_str();  // array name in the shader.
    char locID[100];
    snprintf(locID, 100, "%s[%d].%s", arrayname, i, "on");
    glUniform1i(glGetUniformLocation(fboShader.program, locID), Lt.getOn());

    snprintf(locID, 100, "%s[%d].%s", arrayname, i, "position");
    glUniform4fv(glGetUniformLocation(fboShader.program, locID), 1, glm::value_ptr(Lt.getPosition()));

    snprintf(locID, 100, "%s[%d].%s", arrayname, i, "ambient");
    glUniform4fv(glGetUniformLocation(fboShader.program, locID), 1, glm::value_ptr(Lt.getAmbient()));

    snprintf(locID, 100, "%s[%d].%s", arrayname, i, "diffuse");
    glUniform4fv(glGetUniformLocation(fboShader.program, locID), 1, glm::value_ptr(Lt.getDiffuse()));

    snprintf(locID, 100, "%s[%d].%s", arrayname, i, "specular");
    glUniform4fv(glGetUniformLocation(fboShader.program, locID), 1, glm::value_ptr(Lt.getSpecular()));

    snprintf(locID, 100, "%s[%d].%s", arrayname, i, "spotDirection");
    glUniform3fv(glGetUniformLocation(fboShader.program, locID), 1, glm::value_ptr(Lt.getSpotDirection()));

    snprintf(locID, 100, "%s[%d].%s", arrayname, i, "attenuation");
    glUniform3fv(glGetUniformLocation(fboShader.program, locID), 1, glm::value_ptr(Lt.getAttenuation()));

    snprintf(locID, 100, "%s[%d].%s", arrayname, i, "spotCutoff");
    glUniform1f(glGetUniformLocation(fboShader.program, locID), Lt.getSpotCutoff());

    snprintf(locID, 100, "%s[%d].%s", arrayname, i, "spotExponent");
    glUniform1f(glGetUniformLocation(fboShader.program, locID), Lt.getSpotExponent());
}

/**
\brief Loads the first num entries of a light array to the a light array in the shader.

\param Lt --- Light array to load.

\param name --- The name of the array in the shader.

\param i --- The number of lights to load.

*/

void GraphicsEngine::LoadLights(Light Lt[], std::string name, int num)
{
    for (int i = 0; i < num; i++)
        LoadLight(Lt[i], name.c_str(), i);
}

/**
\brief Turns the light at index i on.

\param name --- The name of the array in the shader.

\param i --- The index of the light to turn on.

*/

void GraphicsEngine::turnLightOn(std::string name, int i)
{
    fboShader.use();

    const char* arrayname = name.c_str();  // array name in the shader.
    char locID[100];
    snprintf(locID, 100, "%s[%d].%s", arrayname, i, "on");
    glUniform1i(glGetUniformLocation(fboShader.program, locID), true);
}

/**
\brief Turns the light at index i off.

\param name --- The name of the array in the shader.

\param i --- The index of the light to turn off.

*/

void GraphicsEngine::turnLightOff(std::string name, int i)
{
    fboShader.use();

    const char* arrayname = name.c_str();  // array name in the shader.
    char locID[100];
    snprintf(locID, 100, "%s[%d].%s", arrayname, i, "on");
    glUniform1i(glGetUniformLocation(fboShader.program, locID), false);
}

/**
\brief Turns the first num lights on.

\param name --- The name of the array in the shader.

\param num --- Number of lights to turn on.

*/

void GraphicsEngine::turnLightsOn(std::string name, int num)
{
    for (int i = 0; i < num; i++)
        turnLightOn(name.c_str(), i);
}

/**
\brief Turns the first num lights off.

\param name --- The name of the array in the shader.

\param num --- Number of lights to turn off.

*/

void GraphicsEngine::turnLightsOff(std::string name, int num)
{
    for (int i = 0; i < num; i++)
        turnLightOff(name.c_str(), i);
}
