#include "GraphicsEngine.h"

/**
\file GraphicsEngine.cpp
\brief Main graphics driver for the program.

This class extends sf::RenderWindow.

\author
\version   1.2
\date      Written: 2/28/2016  <BR> Revised: 4/1/2016

*/

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
                     sf::ContextSettings(24, 8, 4, 3, 3))
{
    // SFML is nice and keeps all the numbers in order
    // So we can be a bit lazy with the mappings
    int key = sf::Keyboard::Num0;

    materials[key++] = Materials::polishedSilver;
    materials[key++] = Materials::redPlastic;
    materials[key++] = Materials::greenPlastic;
    materials[key++] = Materials::bluePlastic;
    materials[key++] = Materials::brass;
    materials[key++] = Materials::bronze;
    materials[key++] = Materials::polishedBronze;
    materials[key++] = Materials::chrome;
    materials[key++] = Materials::polishedCopper;
    materials[key++] = Materials::polishedGold;

    // Map all the keys to their respective models
    models[sf::Keyboard::Z] = (new teapot())->load(0, 2);
    models[sf::Keyboard::X] = load(Models::create()->createSphereOBJ(1, 20, 20));
    models[sf::Keyboard::C] = load(Models::create()->createTorusOBJ(1, 2, 25, 25));
    models[sf::Keyboard::V] = load(Models::create()->createTrefoilOBJ(0.5, 1.5, 2, 0.2, 1.0, 200, 20));
    models[sf::Keyboard::B] = load(Models::create()->createUmbilicTorusOBJ(100, 20));
    models[sf::Keyboard::N] = load(Models::create()->createBraidedTorusOBJ(0.5, 1.25, 2, 0.2, 1.0, 200, 20));
    models[sf::Keyboard::M] = load(Models::create()->createHelicalTorusOBJ(1.0, 2.0, 0.2, -2*PI, 2*PI, 50, 20));
    models[sf::Keyboard::L] = load(Models::create()->createMobiusOBJ(-0.5, 0.5, 30, 30));
    models[sf::Keyboard::K] = load(Models::create()->createTessellatedWallOBJ(2, 2, 1, 1));
    models[sf::Keyboard::J] = load(Models::create()->createTessellatedWallOBJ(2, 2, 20, 20));

    // teapot is default
    activateModel(sf::Keyboard::Z);

    loadShaders();
    useBasicShader();

    // Initialize some data.
    mode = GL_FILL;
    sscount = 1;
    CameraNumber = 1;
    drawAxes = GL_TRUE;

    // Set position of spherical camera
    sphcamera.setPosition(5, 30, 20);

    glEnable(GL_DEPTH_TEST);

    if (SetVS)
    {
        setVerticalSyncEnabled(true);
        setFramerateLimit(60);
    }
    else
    {
        setVerticalSyncEnabled(false);
        setFramerateLimit(0);
    }

    lt.setLight(true,
                30.0, 30.0, 30.0, 1.0,
                -1.0, -1.0, -1.0,
                0.0, 0.0, 0.0, 1.0,
                1.0, 1.0, 1.0, 1.0,
                1.0, 1.0, 1.0, 1.0,
                180.0, 0.0,
                1.0, 0.0, 0.0
               );

    loadLight(lt);
    activateMaterial(sf::Keyboard::Num1);

    lightobj.createSphereOBJ(0.25, 7, 7);
    lightobj.load(0, 1, 2);
    lightobj.setColor(1, 1, 0);
    lightobj.setDrawBorder(GL_TRUE);

    LtPos.setTheta(45);
    LtPos.setPsi(45);
    LtPos.setR(10);

    // Make it the active window for OpenGL calls, resize to set projection matrix.
    setActive();
    resize();
}

void GraphicsEngine::loadShaders()
{
    std::string vertexShaderLighting =

    "#version 330 core\n"
    "layout(location = 0) in vec4 vposition;\n"
    "layout(location = 1) in vec4 vcolor;\n"
    "layout(location = 2) in vec3 vnormal;\n"
    "uniform mat4 PVM;\n"
    "uniform mat4 Model;\n"
    "uniform mat3 NormalMatrix;\n"
    "out vec4 color;\n"
    "out vec4 position;\n"
    "out vec3 normal;\n"
    "void main()\n"
    "{\n"
    "    color = vcolor;\n"
    "    normal = normalize(NormalMatrix * vnormal);\n"
    "    position = Model * vposition;\n"
    "    gl_Position = PVM * vposition;\n"
    "}\n";

    std::string phongBasic =

    "#version 330 core\n"
    "\n"
    "struct Light\n"
    "{\n"
    "    bool on;             \n"
    "    vec4 position;       \n"
    "    vec3 spotDirection;  \n"
    "    vec4 ambient;        \n"
    "    vec4 diffuse;        \n"
    "    vec4 specular;       \n"
    "    float spotCutoff;    \n"
    "    float spotExponent;  \n"
    "    vec3 attenuation;    \n"
    "};\n"
    "struct Material\n"
    "{\n"
    "    vec4 ambient;     \n"
    "    vec4 diffuse;     \n"
    "    vec4 specular;    \n"
    "    vec4 emission;    \n"
    "    float shininess;  \n"
    "};\n"
    "in vec4 position;\n"
    "in vec4 color;\n"
    "in vec3 normal;\n"
    "uniform Light Lt;\n"
    "uniform Material Mat;\n"
    "uniform vec3 eye;\n"
    "uniform vec4 GlobalAmbient;\n"
    "out vec4 fColor;\n"
    "void main()\n"
    "{\n"
    "    float deg = 0.017453292519943296;\n"
    "    vec4 cc;\n"
    "    cc = color;  \n"
    "    if (Lt.on)  \n"
    "    {\n"
    "        vec3 l = normalize(vec3(Lt.position)-vec3(position));\n"
    "        vec3 r = normalize(2.0*dot(l,normal)*normal - l);\n"
    "        vec3 v = normalize(eye-vec3(position));\n"
    "		 vec3 h = normalize(l + v);\n"
    "        float dfang = max(0.0, dot(l, normal));\n"
    "        float specang = max(0.0, dot(r, v));\n"
    "        vec4 globalAmbientPortion = Mat.ambient*GlobalAmbient;\n"
    "        vec4 ambientPortion = Mat.ambient*Lt.ambient;\n"
    "        vec4 diffusePortion = Mat.diffuse*Lt.diffuse*dfang;\n"
    "        vec4 specularPortion = Mat.specular*Lt.specular*pow(specang, Mat.shininess);\n"
    "        vec4 c = ambientPortion + diffusePortion + specularPortion + globalAmbientPortion + Mat.emission;\n"
    "        cc = min(c, vec4(1.0));\n"
    "    }\n"
    "    fColor = cc;\n"
    "}\n";

    std::string phongHalfway =

    "#version 330 core\n"
    "struct Light\n"
    "{\n"
    "    bool on;             \n"
    "    vec4 position;       \n"
    "    vec3 spotDirection;  \n"
    "    vec4 ambient;        \n"
    "    vec4 diffuse;        \n"
    "    vec4 specular;       \n"
    "    float spotCutoff;    \n"
    "    float spotExponent;  \n"
    "    vec3 attenuation;    \n"
    "};\n"
    "struct Material\n"
    "{\n"
    "    vec4 ambient;     \n"
    "    vec4 diffuse;     \n"
    "    vec4 specular;    \n"
    "    vec4 emission;    \n"
    "    float shininess;  \n"
    "};\n"
    "in vec4 position;\n"
    "in vec4 color;\n"
    "in vec3 normal;\n"
    "uniform Light Lt;\n"
    "uniform Material Mat;\n"
    "uniform vec3 eye;\n"
    "uniform vec4 GlobalAmbient;\n"
    "out vec4 fColor;\n"
    "void main()\n"
    "{\n"
    "    float deg = 0.017453292519943296;\n"
    "    vec4 cc;\n"
    "    cc = color;  \n"
    "    if (Lt.on)  \n"
    "    {\n"
    "		vec3 n = normalize(normal);\n"
    "        vec3 l = normalize(vec3(Lt.position)-vec3(position));\n"
    "        vec3 v = normalize(eye-vec3(position));\n"
    "		vec3 h = normalize(l + v);\n"
    "        float dfang = max(0.0, dot(l, n));\n"
    "        float specang = max(0.0, dot(n, h));\n"
    "        vec4 globalAmbientPortion = Mat.ambient*GlobalAmbient;\n"
    "        vec4 ambientPortion = Mat.ambient*Lt.ambient;\n"
    "        vec4 diffusePortion = Mat.diffuse*Lt.diffuse*dfang;\n"
    "        vec4 specularPortion = Mat.specular*Lt.specular*pow(specang, Mat.shininess);\n"
    "        vec4 c = ambientPortion + diffusePortion + specularPortion + globalAmbientPortion + Mat.emission;\n"
    "        cc = min(c, vec4(1.0));\n"
    "    }\n"
    "    fColor = cc;\n"
    "}\n";

    shaderBasic = LoadShadersFromMemory(vertexShaderLighting, phongBasic);
    shaderHalfway = LoadShadersFromMemory(vertexShaderLighting, phongHalfway);

    if (!shaderBasic || !shaderHalfway)
    {
        std::cerr << "Could not load Shader programs." << std::endl;
        exit(EXIT_FAILURE);
    }
}

/** \brief Convenience method to load models with our attribute IDs */
Models* GraphicsEngine::load(Models* model)
{
    model->load(0, 1, 2);
    return model;
}

/** \brief Updates the shader info, used when the shader program changes */
void GraphicsEngine::updateShader()
{
    // Turn on the shader & get location of transformation matrix.
    glUseProgram(program);
    PVMLoc = glGetUniformLocation(program, "PVM");
    ModelLoc = glGetUniformLocation(program, "Model");
    NormalLoc = glGetUniformLocation(program, "NormalMatrix");

    glm::vec4 GlobalAmbient(0.2, 0.2, 0.2, 1);
    glUniform4fv(glGetUniformLocation(program, "GlobalAmbient"), 1, glm::value_ptr(GlobalAmbient));

    loadMaterial(mat);
}

/** \brief Activates the model mapped to the given key. No effect if the key is unmapped */
void GraphicsEngine::activateModel(int c)
{
    if (models.find(c) != models.end())
    {
        active = models[c];
    }
}

/** \brief Activates the material mapped to the given key. No effect if the key is unmapped */
void GraphicsEngine::activateMaterial(int c)
{
    if (materials.find(c) != materials.end())
    {
        mat = materials[c];
        updateShader();
    }
}

/** \brief Rotates the object by the given amount, where vec is rotation along the x, y, and z axis, respectively */
void GraphicsEngine::rotate(glm::ivec3 vec)
{
    rotation += vec;
    rotation %= 360;
}

/** \brief Translates the object by the given amount */
void GraphicsEngine::translate(glm::vec3 vec)
{
    translation += vec * 0.05f;
}

/** \brief Activates the basic shader */
void GraphicsEngine::useBasicShader()
{
    program = shaderBasic;
    updateShader();
}

/** \brief Activates the halfway shader */
void GraphicsEngine::useHalfwayShader()
{
    program = shaderHalfway;
    updateShader();
}

/**
\brief Destructor

Currently empty, no allocated memory to clear.

*/

GraphicsEngine::~GraphicsEngine() {}

/**
\brief The function responsible for drawing to the OpenGL frame buffer.

This function clears the screen and calls the draw functions of the box and circle.

*/

void GraphicsEngine::display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(program);

    lt.setPosition(glm::vec4(LtPos.getPosition(), 1.0));
    loadLight(lt);

    // Set view matrix via current camera.
    glm::mat4 view(1.0);
    if (CameraNumber == 1)
        view = sphcamera.lookAt();
    else if (CameraNumber == 2)
        view = yprcamera.lookAt();

    glm::vec3 eye;
    if (CameraNumber == 1)
        eye = sphcamera.getPosition();
    else if (CameraNumber == 2)
        eye = yprcamera.getPosition();

    glUniform3fv(glGetUniformLocation(program, "eye"), 1, glm::value_ptr(eye));

    turnLightOff();

    // Set axes scaling.
    glm::mat4 axesscale = glm::scale(glm::mat4(1.0), glm::vec3(10, 10, 10));

    // Load matrix product to shader.
    glUniformMatrix4fv(PVMLoc, 1, GL_FALSE, glm::value_ptr(projection*view*axesscale));

    if (drawAxes)
        coords.draw();

    model = glm::translate(glm::mat4(1), translation);
    model = model * glm::eulerAngleYXZ(rotation.y * degf, rotation.x * degf, rotation.z * degf);

    // Load model matrix.
    glUniformMatrix4fv(ModelLoc, 1, GL_FALSE, glm::value_ptr(model));

    // Extract upper left 3 X 3 from model matrix.
    glm::mat3 nM;
    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++)
            nM[c][r] = model[c][r];

    // Create the Normal Transformation matrix N = (M^(-1))^T, where M is the
    // upper left 3 X 3 from model matrix.
    glm::mat3 normalMatrix = glm::transpose(glm::inverse(nM));

    glUniformMatrix3fv(NormalLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));
    glUniformMatrix4fv(PVMLoc, 1, GL_FALSE, glm::value_ptr(projection*view*model));

    turnLightOn();
    active->draw();

    turnLightOff();
    glm::vec3 ltpos;
    ltpos.x = lt.getPosition().x;
    ltpos.y = lt.getPosition().y;
    ltpos.z = lt.getPosition().z;

    glUniformMatrix4fv(PVMLoc, 1, GL_FALSE, glm::value_ptr(projection*view*(glm::translate(glm::mat4(1.0), ltpos))));
    lightobj.draw();

    sf::RenderWindow::display();
    printOpenGLErrors();
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

/**program
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
    glViewport(0, 0, getSize().x, getSize().y);
    projection = glm::perspective(50.0f*degf, (float)getSize().x/getSize().y, 0.01f, 500.0f);
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

SphericalCamera* GraphicsEngine::getLtPos()
{
    return &LtPos;
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
\brief Sets the boolean to draw the axes or not.

\param b --- Draws the axes if true and not if false.

*/

void GraphicsEngine::setDrawAxes(GLboolean b)
{
    drawAxes = b;
}


/**
\brief Turns the light on

*/

void GraphicsEngine::turnLightOn()
{
    glUseProgram(program);
    glUniform1i(glGetUniformLocation(program, "Lt.on"), true);
}

/**
\brief Turns the light off

*/

void GraphicsEngine::turnLightOff()
{
    glUseProgram(program);
    glUniform1i(glGetUniformLocation(program, "Lt.on"), false);
}

/**
\brief Loads the light structure to the shader light structure.

\param Lt --- Light structure to load.

*/

void GraphicsEngine::loadLight(Light Lt)
{
    glUseProgram(program);

    glUniform1i(glGetUniformLocation(program, "Lt.on"), Lt.getOn());
    glUniform4fv(glGetUniformLocation(program, "Lt.position"), 1, glm::value_ptr(Lt.getPosition()));
    glUniform4fv(glGetUniformLocation(program, "Lt.ambient"), 1, glm::value_ptr(Lt.getAmbient()));
    glUniform4fv(glGetUniformLocation(program, "Lt.diffuse"), 1, glm::value_ptr(Lt.getDiffuse()));
    glUniform4fv(glGetUniformLocation(program, "Lt.specular"), 1, glm::value_ptr(Lt.getSpecular()));
    glUniform3fv(glGetUniformLocation(program, "Lt.spotDirection"), 1, glm::value_ptr(Lt.getSpotDirection()));
    glUniform3fv(glGetUniformLocation(program, "Lt.attenuation"), 1, glm::value_ptr(Lt.getAttenuation()));
    glUniform1f(glGetUniformLocation(program, "Lt.spotCutoff"), Lt.getSpotCutoff());
    glUniform1f(glGetUniformLocation(program, "Lt.spotExponent"), Lt.getSpotExponent());
}

/**
\brief Loads the material structure to the shader material structure.

\param Mat --- Material structure to load.Translates

*/

void GraphicsEngine::loadMaterial(Material Mat)
{
    glUseProgram(program);

    glUniform4fv(glGetUniformLocation(program, "Mat.ambient"), 1, glm::value_ptr(Mat.getAmbient()));
    glUniform4fv(glGetUniformLocation(program, "Mat.diffuse"), 1, glm::value_ptr(Mat.getDiffuse()));
    glUniform4fv(glGetUniformLocation(program, "Mat.specular"), 1, glm::value_ptr(Mat.getSpecular()));
    glUniform4fv(glGetUniformLocation(program, "Mat.emission"), 1, glm::value_ptr(Mat.getEmission()));
    glUniform1f(glGetUniformLocation(program, "Mat.shininess"), Mat.getShininess());
}
