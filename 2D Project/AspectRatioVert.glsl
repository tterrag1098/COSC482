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
layout(location = 2) in vec2 itex_coord;

out vec4 color;
out vec2 tex_coord;

uniform mat4 Projection;

void main()
{
	tex_coord = itex_coord;
    color = icolor;
    gl_Position = Projection*position;
}
