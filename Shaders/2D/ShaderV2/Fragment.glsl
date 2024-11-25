#version 330 core 

layout (location=0) out vec4 FragColor;

in vec3 F_Color;

void main()
{
    FragColor = vec4(F_Color, 1.0);
};