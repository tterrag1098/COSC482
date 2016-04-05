#version 330 core

/**
\file AspectRatioVert.glsl

\brief Simple pass through vertex shader.

This is a simple GLSL pass through vertex shader.

\param [in] icolor --- vec4 color from vertex array.

\param [in] position --- vec4 position from vertex array.

\param [out] color --- vec4 output color to the fragment shader.

*/

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 icolor;

out vec4 color;

uniform mat4 Projection;

void main()
{
    color = icolor;
    gl_Position = Projection*position;
}
