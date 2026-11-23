#version 330 core

in vec3 v_Normal;
out vec4 FragColor;

uniform vec4 u_Color;

void main()
{
    vec3 normal = normalize(v_Normal);
    vec3 lightDirection = normalize(vec3(-0.4, 0.8, 0.6));
    float diffuse = max(dot(normal, lightDirection), 0.0);
    float lighting = 0.3 + diffuse * 0.7;
    FragColor = vec4(u_Color.rgb * lighting, u_Color.a);
}
