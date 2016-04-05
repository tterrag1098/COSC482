#version 330 core

/**
\file PassThroughFrag.glsl

\brief Simple pass through fragment shader.

This is a simple GLSL pass through fragment shader.

\param [in] color --- vec4 color from vertex shader.

*/

in vec4 color;

void main()
{
    gl_FragColor = color;
}
