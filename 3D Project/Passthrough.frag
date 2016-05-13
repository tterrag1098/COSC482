#version 330 core

in vec4 color;
in vec2 tex_coord;

uniform sampler2D tex;
uniform bool useTex;

out vec4 fColor;

void main()
{
    if (useTex)
        fColor = texture(tex, tex_coord);
    else
        fColor = color;
}
