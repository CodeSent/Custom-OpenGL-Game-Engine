#version 330 core 

layout (location=0) in vec3 position; 
layout (location=1) in vec3 a_Color; 

out vec3 F_Color;

void main() { 

	gl_Position = vec4(position,1.0f); 
	F_Color = a_Color;
};
