#version 330 core 

layout (location=0) out vec4 FragColor;

in vec2 f_UV;

uniform sampler2D useTex0;

void main()
{
    FragColor = texture(useTex0,f_UV);
};