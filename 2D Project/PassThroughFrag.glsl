#version 330 core

/**
\file PassThroughFrag.glsl

\brief Simple pass through fragment shader.

This is a simple GLSL pass through fragment shader.

\param [in] color --- vec4 color from vertex shader.

*/

in vec4 color;
in vec2 tex_coord;

uniform sampler2D tex1;
uniform bool useTexture;

out vec4 fColor;

void main()
{
    if (useTexture)
        fColor = texture(tex1, tex_coord);
    else
        fColor = color;
}
