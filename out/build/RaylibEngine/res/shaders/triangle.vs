#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 TexCoord;

uniform float x;
uniform float y;

void main()
{
    vec3 pos = aPos;

    pos.x += 0.5 * cos(x);
    pos.y += 0.5 * sin(y);

    
    gl_Position = vec4(pos, 1.0);
    ourColor = aColor;
    TexCoord = aTexCoord;
}
