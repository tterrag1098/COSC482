#include "BeachBall.h"

/**
\file BeachBall.cpp

\brief Implementation file for the BeachBall class.

\author    
\version   1.2
\date      Written: 2/28/2016  <BR> Revised: 3/28/2016

*/

/**
\brief Constructor

Simply stores the pointer of the GraphicsEngine.

*/

BeachBall::BeachBall() : pos({0, 0, 0}), radius(2.0f)
{
    drawFaces = GL_TRUE;
    drawBorder = GL_FALSE;

    glGenVertexArrays(1, &vboptr);
    glGenBuffers(1, &eboptr);
    glGenBuffers(1, &bufptr);
    glGenVertexArrays(1, &vboptrborder);
    glGenBuffers(1, &eboptrborder);
    glGenBuffers(1, &bufptrborder);

    LoadDataToGraphicsCard();
}

/**
\brief Destructor

Removes allocated data from the graphics card.

*/

BeachBall::~BeachBall()
{
    glBindVertexArray(vboptr);
    glDeleteBuffers(1, &bufptr);
    glDeleteBuffers(1, &eboptr);
    glBindVertexArray(vboptrborder);
    glDeleteBuffers(1, &eboptrborder);
    glDeleteBuffers(1, &bufptrborder);
}

BeachBall* BeachBall::setPos(glm::vec3 p)
{
    pos = p;
    LoadDataToGraphicsCard();
    return this;
}

BeachBall* BeachBall::setRadius(GLfloat r)
{
    radius = r;
    LoadDataToGraphicsCard();
    return this;
}

glm::vec3 BeachBall::getPos()
{
    return pos;
}

/**
\brief Turns on and off the drawing of the box border.

\param d --- True to turn the border drawing on and false for off.

*/

void BeachBall::setDrawBorder(GLboolean d)
{
    drawBorder = d;
}

/**
\brief Turns on and off the drawing of the box faces.

\param d --- True to turn the face drawing on and false for off.

*/

void BeachBall::setDrawFaces(GLboolean d)
{
    drawFaces = d;
}

/**
\brief Returns if the grid border is being drawn.

*/

GLboolean BeachBall::getDrawBorder()
{
    return drawBorder;
}

/**
\brief Returns if the grid faces are being drawn.

*/

GLboolean BeachBall::getDrawFaces()
{
    return drawFaces;
}

/**
\brief Loads the vertex and color data to the graphics card.

*/

void BeachBall::LoadDataToGraphicsCard()
{
    int panels = 6;
    int faces = 30;

    // Number of panels * number of edges per panel * doubled due to colorizing
    int vertCount = panels * (faces + 1) * 2;

    // Number of panels * number of faces * vertices per face + extra 6 vertices for the bottom
    numElements = panels * (faces - 2) * 6 + (panels * 6);

    // We will use the same verts for faces and borders
    glm::vec3 verts[vertCount];

    // But separate colors
    lib::ColorRGB colors[vertCount];
    lib::ColorRGB border_colors[vertCount];

    for (int i = 0; i < panels; i++)
    {
        // longitude value
        float u = ((float) i / panels) * 2 * PI;
        // Iterate over twice, because each panel needs both its edges to be the same color
        // So the pattern is panel 1 left, panel 1 right, panel 2 left (same as panel 1 right), etc.
        for (int j = 0; j <= (faces + 1) * 2; j++)
        {
            // Latitude value
            float v = ((float) (j % (faces + 1)) / faces) * PI;
            // If we are beginning the second pass use the next longitude over
            if (j == faces + 1) {
                u += (2 * PI) / panels;
            }
            int vertIdx = (i * (faces + 1) * 2) + j;
            // Standard parametric equation for sphere
            verts[vertIdx] = (glm::vec3(std::cos(u) * std::sin(v), std::cos(v), std::sin(u) * std::sin(v)) * radius) + pos;
            // Border is all blue
            border_colors[vertIdx] = lib::BLUE;
            // Wrap colors if using more than 6 panels
            switch(i % 6)
            {
            case 0:
                colors[vertIdx] = lib::YELLOW;
                break;
            case 1:
                colors[vertIdx] = lib::GREEN;
                break;
            case 2:
                colors[vertIdx] = lib::RED;
                break;
            case 3:
                colors[vertIdx] = lib::BLUE;
                break;
            case 4:
                colors[vertIdx] = lib::WHITE;
                break;
            case 5:
                colors[vertIdx] = lib::MAGENTA;
                break;
            default:
                break;
            }
        }
    }

    GLushort indices[numElements];
    int index = 0;
    for (int i = 0; i < panels; i++)
    {
        int left = i * (faces + 1) * 2;
        int right = left + faces + 2;
        // Add the top triangle
        indices[index++] = left++;
        indices[index++] = right;
        indices[index++] = left;
        // Add two triangles for each quad in between
        for (int j = 0; j < faces - 2; j++)
        {
            indices[index++] = left++;
            indices[index++] = right;
            indices[index++] = left;
            indices[index++] = left;
            indices[index++] = right++;
            indices[index++] = right;
        }
        // Add the bottom triangle
        indices[index++] = left++;
        indices[index++] = right;
        indices[index++] = left;
    }

    int vPosition = 0;
    int vColor = 1;

    glBindVertexArray(vboptr);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboptr);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, bufptr);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts) + sizeof(colors), NULL, GL_DYNAMIC_DRAW);

    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(verts), verts);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(verts), sizeof(colors), colors);

    glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glVertexAttribPointer(vColor, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(verts)));

    glEnableVertexAttribArray(vPosition);
    glEnableVertexAttribArray(vColor);

    glBindVertexArray(vboptrborder);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboptrborder);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, bufptrborder);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts) + sizeof(border_colors), NULL, GL_DYNAMIC_DRAW);

    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(verts), verts);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(verts), sizeof(border_colors), border_colors);

    glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glVertexAttribPointer(vColor, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(verts)));

    glEnableVertexAttribArray(vPosition);
    glEnableVertexAttribArray(vColor);
}

/**
\brief Draws the beach ball to the screen.

*/

void BeachBall::draw()
{
    if (drawFaces)
    {
        glBindVertexArray(vboptr);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboptr);
        glDrawElements(GL_TRIANGLES, numElements, GL_UNSIGNED_SHORT, NULL);
    }

    if (drawBorder)
    {
        glLineWidth(2);
        glBindVertexArray(vboptrborder);
        glDrawElements(GL_LINE_STRIP, numElements, GL_UNSIGNED_SHORT, NULL);
        glLineWidth(1);
    }
}
