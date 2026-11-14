#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform bool textures;

void main()
{
    if(textures) {
        FragColor = texture(ourTexture, TexCoord);
    } else {
        FragColor = vec4(1.0, 0.0, 0.0, 1.0);
    }
}