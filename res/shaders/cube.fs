#version 330 core

in vec2 TexCoords;

uniform vec3 u_Color;
uniform vec3 u_LightColor;
uniform float alpha;

uniform sampler2D u_Texture;

out vec3 FragColor;

void main()
{
    FragColor = u_Color * u_LightColor * texture(u_Texture, TexCoords).rgb;
}