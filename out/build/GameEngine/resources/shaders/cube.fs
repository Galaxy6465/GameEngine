#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
uniform sampler2D ourTexture;

uniform vec3 objectColor;
uniform vec3 lightColor;

void main()
{   
    vec3 result = texture(ourTexture, TexCoord).rgb * objectColor * lightColor;
    FragColor = vec4(result, 1.0);
}