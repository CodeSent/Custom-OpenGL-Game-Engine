#version 330 core 

layout (location=0) in vec3 position; 

layout (location=1) in vec2 a_UV;

out vec2 f_UV;


void main() { 
	vec4 pos =  vec4(position,1.0f);
	gl_Position = pos; 
	f_UV = a_UV;
};
